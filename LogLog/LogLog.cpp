#include "LogLog.h"

#include <fstream>
#include <algorithm>
//#include <QtCore/QDateTime>
//#include <QtCore/QCoreApplication>
//#include <QtCore/QDir>
#include <Windows.h>
#include <io.h>
#include <direct.h>
#include<time.h>

static const int LOGNAME_MAX_SIZE = 65536;
static const std::string SPLITSTR = "\\";

class LogLog::LogLogPrivate {
public:
	LogLogPrivate()
		:path(""), logLine(0) {

	}
	std::ofstream file;//�ļ���
	std::string path;//�ļ�·��
	std::string logFile;//������־���ļ�
	int logLine;//������־����
	LogOutStream os;//�����
};

LogLog::LogLog(const LOGTYPE type, const char * const fileName, const char* const logFile, const int logLine)
	:_p(new LogLogPrivate()) {
	_p->logFile = logFile;
	_p->logLine = logLine;
	_p->os << GetLogType(type) << getLogTime() << getLogFile() << "[" << getLogLine() << "��]" << ":  ";

	DealWithPath(fileName);

	_p->file.open(_p->path.c_str(), std::ios::app);
}

LogLog::~LogLog(void) {
	if (_p->file.is_open()) {
		_p->os << std::endl;
		_p->file << _p->os.str();
		_p->file.close();
	}
	delete _p;
}

const std::string LogLog::getLogFile() {
	std::string::size_type pos = _p->logFile.find_last_of(SPLITSTR);
	if (pos != std::string::npos)
	{
		return '[' + _p->logFile.substr(pos + 2) + ']';
	}
	return "[]";
}

int LogLog::getLogLine() {
	return _p->logLine;
}

const std::string LogLog::getLogDate() {
	std::string temp = getCurrentTime();
	return temp.substr(0, temp.find(" "));
}

const std::string LogLog::GetLogType(const LOGTYPE type) {
	switch (type) {
	case LOGTYPE_ERROR:
		return "[����]";
	case LOGTYPE_WARNING:
		return "[����]";
	case LOGTYPE_NORMAL:
		return "[��¼]";
	default:
		break;
	}
	return "";
}

const std::string LogLog::getLogTime() {
	std::string temp = getCurrentTime();
	std::string::size_type pos = temp.find_last_of(" ");
	if (pos != std::string::npos)
	{
		return '[' + temp.substr(pos + 1) + ']';
	}
	return "[]";
}

LogLog::LogOutStream& LogLog::stream() {
	return _p->os;
}

const std::string LogLog::getCurrentTime() {
	time_t rawTime(NULL);
	time(&rawTime);

	tm localTime;
	localtime_s(&localTime, &rawTime);

	char currentTime[40] = { 0 };
	strftime(currentTime, 40, "%Y-%m-%d %X",&localTime);
	return currentTime;//QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
}

void LogLog::DealWithPath(const std::string &filePath) {
	std::string path = filePath;
	//ȥ���ļ�����
	int dotPos = filePath.find_last_of(".");
	if (dotPos > 0) {
		path = path.substr(0, dotPos);
	}
	_p->path.append(path).append(getLogDate()).append(".log");
	replaceAllSlice(_p->path);

	if (_p->path[1] != ':') {
		//˵�������·�������Ȼ�ȡexe��Ŀ¼
		char buff[LOGNAME_MAX_SIZE];
		GetModuleFileName(NULL,buff,LOGNAME_MAX_SIZE);
		std::string exePath = buff;// QCoreApplication::applicationFilePath().toStdString();
		replaceAllSlice(exePath);

		//ȥ��exe�ļ����ͣ���ȡĿ¼���������·��
		int pos = exePath.find_last_of(SPLITSTR);
		if (pos > 0) {
			if (strcmp(&_p->path[0], SPLITSTR.c_str()) == 0) {
				_p->path = exePath.substr(0, pos).append(_p->path);
			}
			else {
				_p->path = exePath.substr(0, pos + 1).append(_p->path);
			}
		}
	}
	CreateDir(_p->path);
	//����Ŀ¼�㼶�����û�еĻ���
	//std::string::size_type pos = _p->path.find_last_of(SPLITSTR);
	//if (pos != std::string::npos && pos > 0) {
	//	QDir dirPath(QString::fromStdString(_p->path.substr(0, pos)));
	//	if (!dirPath.exists()) {
	//		dirPath.mkpath(dirPath.path());
	//	}
	//}
}

void LogLog::replaceAllSlice(std::string &data, const std::string &oldVal /*= "/"*/, const std::string &newVal /*= "\\"*/) const
{
	while (true)
	{
		std::string::size_type pos = data.find(oldVal);
		if (pos != std::string::npos)
		{
			data.replace(pos, oldVal.length(), newVal);
		}
		else
		{
			return;
		}
	}
}

void LogLog::CreateDir(const std::string &dirPath)
{
	std::string::size_type splitPos = dirPath.find_first_of(SPLITSTR);

	while (true)
	{
		splitPos = dirPath.find(SPLITSTR, splitPos + 1);
		if (splitPos != std::string::npos)
		{
			std::string path = dirPath.substr(0, splitPos);
			if (::_access(path.c_str(),0) != 0)
			{//˵�������ڸ�Ŀ¼������֮
				if (::_mkdir(path.c_str()) != 0)
				{
					return;
				}
			}
		}
		else
		{
			return;
		}
	}
}
