#ifndef LogLog_global_h__
#define LogLog_global_h__

#ifdef LOGLOG_LIB
#define LOGLOG_LIB_EXPORT _declspec(dllexport)
#else
#define LOGLOG_LIB_EXPORT _declspec(dllimport)
#endif
#endif // LogLog_global_h__