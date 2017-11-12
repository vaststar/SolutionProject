#ifndef PluginManager_h__
#define PluginManager_h__

#include "PluginCore_global.h"
#include <vector>
#include <string>
///////////////////////////////////////////////////////////////////////////
///<summary> 插件管理类 .</summary>//////////////////////////////////////////////////
///
///<remarks>  朱正天，2017/7/12.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class PluginBase;
class PluginFactory;

class PLUGINCORE_LIB_EXPORT PluginManager
{
public:
	///<summary> 插件管理入口 朱正天，2017/7/12.</summary>///
	static PluginManager* Instance();

public:
	void startManager();

public:
	///<summary> 根据名称获取插件指针 朱正天，2017/7/12.</summary>///
	PluginBase* GetPluginByName(const std::string &pluginName)const;

	///<summary> 获取所有已经加载的插件 朱正天，2017/7/12.</summary>///
	const std::vector<PluginBase*> GetAllPlugins()const;

public:
	///<summary> 根据名称加载插件 朱正天，2017/7/12.</summary>///
	PluginBase* LoadPluginByName(const std::string &pluginName);

private:

	///<summary> 获取插件核心路径 朱正天，2017/7/12.</summary>///
	const std::string GetCoreDLLPath()const;

	///<summary> 根据插件类名，获取插件动态库绝对路径 朱正天，2017/7/12.</summary>///
	const std::string GetPluginDLLPath(const std::string &pluginName)const;

private:
	///<summary> 初始化配置文件、路径等 朱正天，2017/7/12.</summary>///
	void InitStuff();
	void InitConfig();
	void InitCorePath();

	///<summary> 加载配置文件中的所有插件 朱正天，2017/7/12.</summary>///
	void LoadAllPlugins();

private:
	///////////////////////////////////////////////////////////////////////////
	///<summary> 根据插件类名，创建类指针（如果已经存在，则直接返回该指针） .</summary>/////////////////////////////////////////////
	///<params>	 类名				</params>////
	///<return>	 指针				</return>////
	///<remarks>  朱正天，2017/7/12.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	PluginBase *CreateIndicatorFromName(const std::string &pluginName);

private:
	PluginManager(void);
	~PluginManager(void);
	PluginManager(const PluginManager &r);
	PluginManager &operator=(const PluginManager& r);

private:
	class PluginManagerPrivate;
	PluginManagerPrivate *_p;
	static PluginManager *m_manager;
public:
	///<summary> 注册插件（外部请勿使用） 朱正天，2017/7/12.</summary>///
	void RegisterPluginToMap(const std::string &pluginName, PluginFactory *factory);
};
#endif // PluginManager_h__

