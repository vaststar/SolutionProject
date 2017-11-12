#ifndef DataStructType_global_h__
#define DataStructType_global_h__

#ifdef DATASTRUCTTYPE_LIB
#define DATASTRUCTTYPE_LIB_EXPORT __declspec(dllexport)
#else
#define DATASTRUCTTYPE_LIB_EXPORT __declspec(dllimport)
#endif

#endif // DataStructType_global_h__
