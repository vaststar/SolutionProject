#include "FacilityUtil.h"

#include <iostream>
#include <io.h>
#include <direct.h>
#include <time.h>

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

bool FacilityUtil::CreateDirPath(const std::string &path, const std::string &splitCh) 
{
	if (path.size() < 4 || path[1] != ':') return false;

	std::string::size_type splitPos = path.find_last_of(splitCh);
	while ((splitPos = path.find(splitCh,splitPos +1)) != std::string::npos)
	{
		std::string subPath = path.substr(0, splitPos);
		if (0 != ::_access(subPath.c_str(),0))
		{
			if (0 != ::_mkdir(path.c_str()))
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