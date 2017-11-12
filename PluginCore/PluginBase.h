#ifndef PluginBase_h__
#define PluginBase_h__

#include <string>
#include "PluginCore_global.h"
//////////////////////////////////////////////////////////////////////////
///<summary> 插件基类 </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class QIcon;
class PLUGINCORE_LIB_EXPORT PluginBase {
public:
	PluginBase(void);
	~PluginBase(void);
public:
	virtual void InitialLize() = 0;
	virtual const std::string getName() const = 0;
	virtual const std::string getDescribe() const = 0;
	virtual const QIcon getIcon()const = 0;
};
#endif // PluginBase_h__

