#ifndef PluginFactory_h__
#define PluginFactory_h__

#include "PluginCore_global.h"
class PluginBase;
class PLUGINCORE_LIB_EXPORT PluginFactory {
public:
	PluginFactory(void);
	~PluginFactory(void);
public:
	virtual PluginBase * CreatePlugin() = 0;
};
#endif // PluginFactory_h__

