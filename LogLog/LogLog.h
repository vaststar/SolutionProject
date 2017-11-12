#ifndef LogLog_h__
#define LogLog_h__

#include <sstream>
#include "LogLog_global.h"
///////////////////////////////////////////////////////////////////////////
///<summary> �붨������־�� .</summary>//////////////////////////////////////////////////
///
///<remarks>  �����죬2017/7/4.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class LOGLOG_LIB_EXPORT LogLog
{
	typedef std::ostringstream LogOutStream;
public:
	enum LOGTYPE
	{
		LOGTYPE_ERROR = 0,//����
		LOGTYPE_WARNING = 1,//����
		LOGTYPE_NORMAL = 2//����
	};
public:
	LogLog(const LOGTYPE type, const char * const fileName, const char* const logFile, const int logLine);
	~LogLog(void);
public:
	///<summary> ��������� �����죬2017/7/5.</summary>///
	LogOutStream& stream();

private:
	///<summary> ������־���� �����죬2017/7/5.</summary>///
	const std::string GetLogType(const LOGTYPE);

	///<summary> ��ȡ��ǰʱ�䣨xxʱxx��xx�룩 �����죬2017/7/5.</summary>///
	const std::string getLogTime();

	///<summary> ��ȡ��ǰ���ڣ�xxxx��xx��xx�գ� �����죬2017/7/5.</summary>///
	const std::string getLogDate();

	///<summary> ��ȡlog�����к� �����죬2017/7/5.</summary>///
	int getLogLine();

	///<summary> ��ȡ������log����·�����ļ���·���� �����죬2017/7/5.</summary>///
	const std::string getLogFile();

private:

	///<summary> ��ȡ��ǰʱ�� �����죬2017/7/5.</summary>///
	const std::string getCurrentTime();
	///<summary> ����·������ �����죬2017/7/5.</summary>///
	void DealWithPath(const std::string &filePath);

	//<summary> �滻�ַ����е���б�� 2017/11/9--������ </summary> 
	void replaceAllSlice(std::string &data,const std::string &oldVal = "/",const std::string &newVal = "\\")const;

	//<summary> ����·�������ļ���Ŀ¼ 2017/11/9--������ </summary> 
	void CreateDir(const std::string &dirPath);
private:
	class LogLogPrivate;
	LogLogPrivate *_p;
};

#define INITLOG_ERROR(fileName) LogLog(LogLog::LOGTYPE_ERROR,fileName,__FILE__,__LINE__).stream()
#define INITLOG_WARNING(fileName) LogLog(LogLog::LOGTYPE_WARNING,fileName,__FILE__,__LINE__).stream()
#define INITLOG_NORMAL(fileName) LogLog(LogLog::LOGTYPE_NORMAL,fileName,__FILE__,__LINE__).stream()
#endif // LogLog_h__
