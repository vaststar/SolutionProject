#ifndef LogDefine_h__
#define LogDefine_h__

#include "LogLog.h"

static const char* FILENAME = "Log\\MyLog";//设置输出目录为（.exe目录下的MyLog文件夹下的“想定生成xxxx年xx月xx日.log”）
#define  ERROR_LOG \
	INITLOG_ERROR(FILENAME)
#define  WARNING_LOG \
	INITLOG_WARNING(FILENAME)
#define  NORMAL_LOG \
	INITLOG_NORMAL(FILENAME)

#endif // LogDefine_h__