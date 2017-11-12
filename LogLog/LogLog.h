#ifndef LogLog_h__
#define LogLog_h__

#include <sstream>
#include "LogLog_global.h"
///////////////////////////////////////////////////////////////////////////
///<summary> 想定生成日志类 .</summary>//////////////////////////////////////////////////
///
///<remarks>  朱正天，2017/7/4.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class LOGLOG_LIB_EXPORT LogLog
{
	typedef std::ostringstream LogOutStream;
public:
	enum LOGTYPE
	{
		LOGTYPE_ERROR = 0,//错误
		LOGTYPE_WARNING = 1,//警告
		LOGTYPE_NORMAL = 2//正常
	};
public:
	LogLog(const LOGTYPE type, const char * const fileName, const char* const logFile, const int logLine);
	~LogLog(void);
public:
	///<summary> 对外输出流 朱正天，2017/7/5.</summary>///
	LogOutStream& stream();

private:
	///<summary> 设置日志类型 朱正天，2017/7/5.</summary>///
	const std::string GetLogType(const LOGTYPE);

	///<summary> 获取当前时间（xx时xx分xx秒） 朱正天，2017/7/5.</summary>///
	const std::string getLogTime();

	///<summary> 获取当前日期（xxxx年xx月xx日） 朱正天，2017/7/5.</summary>///
	const std::string getLogDate();

	///<summary> 获取log产生行号 朱正天，2017/7/5.</summary>///
	int getLogLine();

	///<summary> 获取处理后的log产生路径（文件简化路径） 朱正天，2017/7/5.</summary>///
	const std::string getLogFile();

private:

	///<summary> 获取当前时间 朱正天，2017/7/5.</summary>///
	const std::string getCurrentTime();
	///<summary> 处理路径问题 朱正天，2017/7/5.</summary>///
	void DealWithPath(const std::string &filePath);

	//<summary> 替换字符串中的正斜杠 2017/11/9--朱正天 </summary> 
	void replaceAllSlice(std::string &data,const std::string &oldVal = "/",const std::string &newVal = "\\")const;

	//<summary> 根据路径创建文件夹目录 2017/11/9--朱正天 </summary> 
	void CreateDir(const std::string &dirPath);
private:
	class LogLogPrivate;
	LogLogPrivate *_p;
};

#define INITLOG_ERROR(fileName) LogLog(LogLog::LOGTYPE_ERROR,fileName,__FILE__,__LINE__).stream()
#define INITLOG_WARNING(fileName) LogLog(LogLog::LOGTYPE_WARNING,fileName,__FILE__,__LINE__).stream()
#define INITLOG_NORMAL(fileName) LogLog(LogLog::LOGTYPE_NORMAL,fileName,__FILE__,__LINE__).stream()
#endif // LogLog_h__
