#ifndef LogDefine_h__
#define LogDefine_h__

#include "LogLog.h"

static const char* FILENAME = "Log\\MyLog";//�������Ŀ¼Ϊ��.exeĿ¼�µ�MyLog�ļ����µġ��붨����xxxx��xx��xx��.log����
#define  ERROR_LOG \
	INITLOG_ERROR(FILENAME)
#define  WARNING_LOG \
	INITLOG_WARNING(FILENAME)
#define  NORMAL_LOG \
	INITLOG_NORMAL(FILENAME)

#endif // LogDefine_h__