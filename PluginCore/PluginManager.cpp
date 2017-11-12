#include "PluginManager.h"

#include "PluginBase.h"
#include "PluginFactory.h"

#include <map>
#include <vector>
#include <Windows.h>

#include <FacilityUtil/FacilityUtil.h>

static const std::string PluginConfig = "Config/PluginConfig.json";

class PluginManager::PluginManagerPrivate {
public:
	PluginManagerPrivate()
		:m_coreDllPath("") {

	}
	~PluginManagerPrivate() {
		for (auto it = m_vecPlugins.begin(); it != m_vecPlugins.end(); ++it) {
			delete *it;
			*it = nullptr;
		}
		for (auto it = m_vecPluginLibs.begin(); it != m_vecPluginLibs.end(); ++it) {
			delete (*it).second;
			(*it).second = nullptr;
		}
	}
public:
	std::vector<PluginBase*> m_vecPlugins;//插件实例
	std::map<std::string, std::vector<std::string>> m_pluginConfig;//插件配置文件
	std::string m_coreDllPath;//核心路径
	std::map<std::string, PluginFactory*> m_vecPluginLibs;//插件名称及对应的工厂
};

PluginManager::PluginManager(void)
	:_p(new PluginManagerPrivate()) {
}

PluginManager::~PluginManager(void) {
	delete _p;
}

PluginManager *PluginManager::m_manager = nullptr;
HANDLE g_mutex = CreateMutex(NULL, FALSE, NULL);
PluginManager* PluginManager::Instance() {
	if (m_manager == NULL) {
		::WaitForSingleObject(g_mutex, INFINITE);
		if (m_manager == NULL) {
			m_manager = new PluginManager();
		}
		ReleaseMutex(g_mutex);
	}
	return m_manager;
}

void PluginManager::startManager() {
	static bool isInited = false;
	if (isInited == false) {
		InitStuff();
		LoadAllPlugins();
		isInited = true;
	}
}

PluginBase* PluginManager::LoadPluginByName(const std::string &pluginName) {
	for (std::vector<PluginBase*>::const_iterator it = _p->m_vecPlugins.begin(); it != _p->m_vecPlugins.end(); ++it) {
		std::string className = typeid(**it).name();
		if (pluginName == className.substr(className.find_last_of(" ") + 1, strlen(className.c_str()))) {
			return *it;
		}
	}
	if (PluginBase *plugin = CreateIndicatorFromName(pluginName)) {
		_p->m_vecPlugins.push_back(plugin);
		return plugin;
	}
	return nullptr;
}

void PluginManager::InitStuff() {
	InitCorePath();
	InitConfig();
}

const std::string PluginManager::GetCoreDLLPath()const {
	return _p->m_coreDllPath;
}

void PluginManager::InitCorePath() {
#ifdef NDEBUG
	HMODULE moduleH = GetModuleHandle("PluginCore.dll");
#else
	HMODULE moduleH = GetModuleHandle("PluginCored.dll");
#endif
	if (moduleH) {
		char buffer[MAX_PATH];
		GetModuleFileName(moduleH, buffer, sizeof(buffer) / sizeof(char) - 1);
		std::string dllPath = buffer;
		int index = dllPath.find_last_of("\\");
		_p->m_coreDllPath = dllPath.substr(0, index + 1);
	}
}

void PluginManager::InitConfig() {
	FacilityUtil::ParseJsonFile(std::string().append(GetCoreDLLPath()).append(PluginConfig), _p->m_pluginConfig);
}

void PluginManager::LoadAllPlugins() {
	for (std::map<std::string, std::vector<std::string>>::const_iterator it = _p->m_pluginConfig.begin(); it != _p->m_pluginConfig.end(); ++it) {
		if ((*it).second.size() >= 3 && (*it).second[2] == "true") {
			LoadPluginByName((*it).first);
		}
	}
}

const std::string PluginManager::GetPluginDLLPath(const std::string &pluginName) const {
	std::map<std::string, std::vector<std::string>>::const_iterator it = _p->m_pluginConfig.find(pluginName);
	if (it != _p->m_pluginConfig.end()) {
		if ((*it).second.size() >= 2) {
			if ((*it).second[1].back() != '\\' || (*it).second[1].back() != '/') {
				return std::string().append((*it).second[1]).append("/");
			}
			else {
				return (*it).second[1];
			}
		}
	}
	return "";
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////关键类方法，外部不可调用////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PluginManager::RegisterPluginToMap(const std::string &pluginName, PluginFactory *factory) {
	std::map<std::string, PluginFactory*>::iterator it = _p->m_vecPluginLibs.find(pluginName);
	if (it == _p->m_vecPluginLibs.end()) {
		_p->m_vecPluginLibs[pluginName] = factory;
	}
}

PluginBase * PluginManager::CreateIndicatorFromName(const std::string &pluginName) {
	std::map<std::string, PluginFactory*>::const_iterator it = _p->m_vecPluginLibs.find(pluginName);
	if (it == _p->m_vecPluginLibs.end()) {
#ifdef NDEBUG
		::LoadLibrary(std::string(GetPluginDLLPath(pluginName)).append(pluginName).append(".dll").c_str());
#else
		::LoadLibrary(std::string(GetPluginDLLPath(pluginName)).append(pluginName).append("d.dll").c_str());
#endif
		it = _p->m_vecPluginLibs.find(pluginName);
	}
	if (it == _p->m_vecPluginLibs.end()) return nullptr;

	return (*it).second->CreatePlugin();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////关键类方法，外部不可调用////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::vector<PluginBase*> PluginManager::GetAllPlugins() const {
	return _p->m_vecPlugins;
}

PluginBase* PluginManager::GetPluginByName(const std::string &pluginName)const {
	for (std::vector<PluginBase*>::const_iterator it = _p->m_vecPlugins.begin(); it != _p->m_vecPlugins.end(); ++it) {
		std::string className = typeid(**it).name();
		if (pluginName == className.substr(className.find_last_of(" ") + 1, strlen(className.c_str()))) {
			return *it;
		}
	}
	return nullptr;
}