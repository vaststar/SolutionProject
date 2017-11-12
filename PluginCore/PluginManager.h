#ifndef PluginManager_h__
#define PluginManager_h__

#include "PluginCore_global.h"
#include <vector>
#include <string>
///////////////////////////////////////////////////////////////////////////
///<summary> ��������� .</summary>//////////////////////////////////////////////////
///
///<remarks>  �����죬2017/7/12.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////

class PluginBase;
class PluginFactory;

class PLUGINCORE_LIB_EXPORT PluginManager
{
public:
	///<summary> ���������� �����죬2017/7/12.</summary>///
	static PluginManager* Instance();

public:
	void startManager();

public:
	///<summary> �������ƻ�ȡ���ָ�� �����죬2017/7/12.</summary>///
	PluginBase* GetPluginByName(const std::string &pluginName)const;

	///<summary> ��ȡ�����Ѿ����صĲ�� �����죬2017/7/12.</summary>///
	const std::vector<PluginBase*> GetAllPlugins()const;

public:
	///<summary> �������Ƽ��ز�� �����죬2017/7/12.</summary>///
	PluginBase* LoadPluginByName(const std::string &pluginName);

private:

	///<summary> ��ȡ�������·�� �����죬2017/7/12.</summary>///
	const std::string GetCoreDLLPath()const;

	///<summary> ���ݲ����������ȡ�����̬�����·�� �����죬2017/7/12.</summary>///
	const std::string GetPluginDLLPath(const std::string &pluginName)const;

private:
	///<summary> ��ʼ�������ļ���·���� �����죬2017/7/12.</summary>///
	void InitStuff();
	void InitConfig();
	void InitCorePath();

	///<summary> ���������ļ��е����в�� �����죬2017/7/12.</summary>///
	void LoadAllPlugins();

private:
	///////////////////////////////////////////////////////////////////////////
	///<summary> ���ݲ��������������ָ�루����Ѿ����ڣ���ֱ�ӷ��ظ�ָ�룩 .</summary>/////////////////////////////////////////////
	///<params>	 ����				</params>////
	///<return>	 ָ��				</return>////
	///<remarks>  �����죬2017/7/12.</remarks>/////////////////////////////////
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
	///<summary> ע�������ⲿ����ʹ�ã� �����죬2017/7/12.</summary>///
	void RegisterPluginToMap(const std::string &pluginName, PluginFactory *factory);
};
#endif // PluginManager_h__

