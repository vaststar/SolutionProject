#ifndef DataBaseOperate_global_h__
#define DataBaseOperate_global_h__

#ifdef DATABASEOPERATE_LIB
#define DATABASEOPERATE_LIB_EXPORT _declspec(dllexport)
#else
#define DATABASEOPERATE_LIB_EXPORT _declspec(dllimport)
#endif

#endif // DataBaseOperate_global_h__
