#include "FacilityUtil.h"

#include <iostream>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <algorithm>
#include <fstream>

#include <Windows.h>
#include <TlHelp32.h>
#include <objbase.h>
#pragma comment(lib, "ole32.lib")

#include <rapidjson/rapidjson.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>


FacilityUtil::FacilityUtil()
{
}

FacilityUtil::~FacilityUtil()
{
}

void FacilityUtil::TerminateProcessByName(const std::string &processName) 
{
	DWORD ID = 0;
	if (GetProcessIDByName(processName,ID))
	{
		if (HANDLE handle = OpenProcess(PROCESS_TERMINATE,FALSE,ID))
		{
			TerminateProcess(handle, 0);
		}
	}
}

const std::string FacilityUtil::GenerateUUID() 
{
	static char buf[64] = { 0 };
	GUID guid;
	if (S_OK == ::CoCreateGuid(&guid))
	{
		_snprintf_s(buf, sizeof(buf), "%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X"
			, guid.Data1, guid.Data2, guid.Data3\
			, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4]\
			, guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	}
	return buf;
}

bool FacilityUtil::CreateDirPath(const std::string &path, const std::string &splitCh, bool isDir)
{
	if (path.size() < 4 || splitCh.empty() ||
		path[1] != ':' || path[2] != splitCh.front()) return false;

	std::string usedPath = path;
	if (isDir)
	{
		if (path.back() != splitCh.front())
		{
			usedPath.append(splitCh);
		}
	}

	std::string::size_type splitPos = usedPath.find_first_of(splitCh);
	while ((splitPos = usedPath.find(splitCh,splitPos +1)) != std::string::npos)
	{
		std::string subPath = usedPath.substr(0, splitPos);
		if (0 != ::_access(subPath.c_str(),0))
		{
			if (0 != ::_mkdir(subPath.c_str()))
			{
				return false;
			}
		}
	}
	return true;
}

void FacilityUtil::ReplaceStringAll(std::string &sourceStr, const std::string &oldStr, const std::string &newStr) 
{
	while (true)
	{
		std::string::size_type pos = sourceStr.find(oldStr);
		if (pos == std::string::npos) return;
		sourceStr.replace(pos, oldStr.length(), newStr);
	}
}

const std::string FacilityUtil::GetDateTime(const std::string &dateStyle /*= "%Y-%m-%d %H:%M:%S"*/, 
											std::vector<int> &result /*= std::vector<int>()*/) 
{
	time_t calendarTime(0);
	time(&calendarTime);
	tm currentTime;
	localtime_s(&currentTime, &calendarTime);

	result.clear();
	result.resize(9);
	result = {currentTime.tm_sec,currentTime.tm_min,currentTime.tm_hour,currentTime.tm_mday,currentTime.tm_mon+1,currentTime.tm_year+1900,\
			  currentTime.tm_wday,currentTime.tm_yday,currentTime.tm_isdst};
	char buf[1024] = {0};
	strftime(buf, sizeof(buf), dateStyle.c_str(), &currentTime);
	return buf;
}


bool FacilityUtil::GetProcessIDByName(const std::string &processName, unsigned long &Results)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == FALSE)
	{
		std::cout << "创建进程快照失败" << std::endl;
		return false;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRect = Process32First(hSnapshot, &pe32);
	while (bRect)
	{
		if (strcmp(processName.c_str(), pe32.szExeFile) == 0)
		{
			Results = pe32.th32ProcessID;
			CloseHandle(hSnapshot);
			return true;
		}
		bRect = Process32Next(hSnapshot, &pe32);
	}
	CloseHandle(hSnapshot);
	std::cout << "找不到 " << processName << " 对应的进程" << std::endl;
	return false;
}


bool FacilityUtil::GetAllPath(const std::string &sourcePath, std::vector<std::string> &dirResult, 
							  std::vector<std::string> &fileResult, bool isDir)
{
	if (sourcePath.size() < 2 || sourcePath[1] != ':') return false;
	long hFile = 0;
	_finddata32_t fileInfo;

	std::string usedPath = sourcePath;
	if (isDir)
	{
		if (sourcePath.back() == '\\' || sourcePath.back() == '/')
		{
			usedPath.pop_back();
		}
		if ((hFile = _findfirst32(std::string().append(usedPath).append("\\*").c_str(), &fileInfo)) == -1) return false;
	} 
	else
	{
		fileResult.push_back(sourcePath);
		return true;
	}
	do 
	{
		if (fileInfo.attrib & _A_SUBDIR)
		{
			if (strcmp(fileInfo.name, ".") == 0 || strcmp(fileInfo.name, "..") == 0) continue;
			
			dirResult.push_back(std::string().append(usedPath).append("\\").append(fileInfo.name));
			GetAllPath(std::string().append(usedPath).append("\\").append(fileInfo.name), dirResult,fileResult,true);
		} 
		else
		{
			fileResult.push_back(std::string().append(usedPath).append("\\").append(fileInfo.name));
		}
	} while (_findnext32(hFile,&fileInfo) == 0);
	_findclose(hFile);
	return true;
}

///////////////////////////////////////////////////////////////////////////
///<summary> 将json文档，解析成map（key=string,value=string）(无法解析kObjectType)(数组去除首尾空白后通过下划线连接) .</summary>/////////////////////////////////////////////
///<params>		json字符串， 结果map			</params>////
///<return>		成功解析返回true，否则返回false			</return>////
///<remarks>  朱正天，2017/6/27.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////
const bool ParseJsonDoc(const RAPIDJSON_NAMESPACE::Document &document, std::map<std::string, std::vector<std::string>> &Result)
{
	Result.clear();
	for (RAPIDJSON_NAMESPACE::Value::ConstMemberIterator it = document.MemberBegin(); it != document.MemberEnd(); ++it)
	{
		std::string key = it->name.GetString();
		std::vector<std::string> val;
		bool IsRecongnisable = true;
		switch (it->value.GetType())
		{
		case RAPIDJSON_NAMESPACE::kNullType:
			val.push_back("");
			break;
		case RAPIDJSON_NAMESPACE::kFalseType:
			val.push_back("false");
			break;
		case RAPIDJSON_NAMESPACE::kTrueType:
			val.push_back("true");
			break;
		case RAPIDJSON_NAMESPACE::kStringType:
			val.push_back(it->value.GetString());
			break;
		case RAPIDJSON_NAMESPACE::kNumberType:
			if (it->value.IsInt())
			{
				val.push_back(std::to_string(it->value.GetInt()));
			}
			else if (it->value.IsDouble())
			{
				val.push_back(std::to_string(it->value.GetDouble()));
			}
			break;
		case RAPIDJSON_NAMESPACE::kObjectType:
			IsRecongnisable = false;
			break;
		case RAPIDJSON_NAMESPACE::kArrayType:
			for (RAPIDJSON_NAMESPACE::Value::ConstValueIterator arr = it->value.Begin(); arr != it->value.End(); ++arr)
			{
				if (arr->IsString())
				{
					val.push_back(arr->GetString());
				}
				else if (arr->IsInt())
				{
					val.push_back(std::to_string(arr->GetInt()));
				}
				else if (arr->IsDouble())
				{
					val.push_back(std::to_string(arr->GetDouble()));
				}
				else if (arr->IsFalse())
				{
					val.push_back("false");
				}
				else if (arr->IsTrue())
				{
					val.push_back("true");
				}
				else if (arr->IsNull())
				{
					val.push_back("");
				}
			}
			break;
		
		default:
			break;
		}
		if (!IsRecongnisable) continue;
		Result[key] = val;
	}

	return true;
}

bool FacilityUtil::ParseJsonString(const std::string &jsonString, std::map<std::string, std::vector<std::string>> &Results)
{
	if (jsonString.empty()) return false;
	RAPIDJSON_NAMESPACE::Document document;
	if (document.Parse(jsonString.c_str()).HasParseError()) return false;

	return ParseJsonDoc(document, Results);
}

bool FacilityUtil::ParseJsonFile(const std::string &filePath, std::map<std::string, std::vector<std::string>> &Results)
{
	FILE *pFile = nullptr;
	fopen_s(&pFile, filePath.c_str(), "r");
	if (pFile)
	{
		char buffer[65536];
		RAPIDJSON_NAMESPACE::FileReadStream is(pFile, buffer, sizeof(buffer));

		RAPIDJSON_NAMESPACE::Document document;
		if (document.ParseStream<0, RAPIDJSON_NAMESPACE::UTF8<>, RAPIDJSON_NAMESPACE::FileReadStream>(is).HasParseError()) return false;
		return ParseJsonDoc(document, Results);
	}
	return false;
}

bool FacilityUtil::CopyFileToTarget(const std::string &sourcePath, const std::string &dirPath, 
									bool replace/*=true*/, const std::string &fileType/*=""*/)
{
	if (sourcePath.size() < 2 || dirPath.size() < 2 ||sourcePath[1] != ':' || dirPath[1] != ':') return false;
	std::vector<std::string> dir, file;
	GetAllPath(sourcePath, dir, file);

	//创建文件夹
	std::for_each(dir.begin(), dir.end(), [sourcePath,dirPath](const std::string &data) {
		std::string path = dirPath;
		path.append(data.substr(sourcePath.length(), data.size()));
		CreateDirPath(path, std::string() + sourcePath[2], true);
	});

	//复制文件
	std::for_each(file.begin(), file.end(), [sourcePath,dirPath,replace](const std::string &data) {
		std::string outPath = dirPath + data.substr(sourcePath.length(), data.size());

		if (!replace && ::_access(outPath.c_str(), 0) == 0) return;

		std::ifstream in;
		in.open(data.c_str(),std::ios_base::in | std::ios_base::binary);
		if (!in.is_open()) return;

		std::ofstream out;
		out.open(outPath.c_str(),std::ios_base::out | std::ios_base::binary);
		if (!out.is_open()) return;
		
		out << in.rdbuf();
		in.close();
		out.close();
	});
	return true;
}
