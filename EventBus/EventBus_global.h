#ifndef EventBus_global_h__
#define EventBus_global_h__

#ifdef EVENTBUS_LIB
#define EVENTBUS_LIB_EXPORT __declspec(dllexport)
#else
#define EVENTBUS_LIB_EXPORT __declspec(dllimport)
#endif
#endif // EventBus_global_h__
