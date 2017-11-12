#ifndef Register_h__
#define Register_h__

#include "PluginBase.h"
#include "PluginFactory.h"
#include "PluginManager.h"

#define REGISTER_PLUGIN(class_name)\
class PluginFactory_##class_name:public PluginFactory{\
public:\
	virtual PluginBase *CreatePlugin(){\
		return new class_name;}\
};\
int register_factory_##class_name(){\
	PluginManager::Instance()->RegisterPluginToMap(#class_name , new PluginFactory_##class_name);\
	return 0;\
}\
static int register_##class_name = register_factory_##class_name();

#endif // Register_h__