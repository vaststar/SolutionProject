#ifndef PluginCore_global_h__
#define PluginCore_global_h__

#ifdef PLUGINCORE_LIB
#define PLUGINCORE_LIB_EXPORT _declspec(dllexport)
#else
#define PLUGINCORE_LIB_EXPORT _declspec(dllimport)
#endif
#endif // PluginCore_global_h__
