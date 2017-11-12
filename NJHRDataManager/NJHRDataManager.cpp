#include "NJHRDataManager.h"

#include <QtCore/QCoreApplication>

#include <LogLog/LogDefine.h>
#include <NJHRShootDataType/NJHRShootDataType.h>
#include <NJHRShootUtil/NJHRShootUtil.h>
#include <NJHRShootDataAccess/NJHRShootDataAccess.h>

static const std::string ConfigDir = "\\Config\\DataBase.config";//���ݿ�������

class NJHRDataManager::NJHRDataManagerPrivate
{
public:
	NJHRDataManagerPrivate()
	{

	}
public:
	NJHRShootDataAccess _dataAccess;//���ݿ������

	SoldierBaseInfoVec _allSoldiers;//������Ա

	UserPassWordTabVec _allPassword;//���������
};

NJHRDataManager::NJHRDataManager()
	:_p(new NJHRDataManagerPrivate())
{
	StartDataBase();
	InitData();
}

NJHRDataManager::~NJHRDataManager()
{
	delete _p;
}

NJHRDataManager * NJHRDataManager::_instance = nullptr;

NJHRDataManager * NJHRDataManager::Instance()
{
	if (nullptr == _instance)
	{
		_instance = new NJHRDataManager();
	}
	return _instance;
}

bool NJHRDataManager::StartDataBase()
{
	 std::string configPath = QCoreApplication::applicationDirPath().append(ConfigDir.c_str()).toStdString();
	 std::map<std::string, std::vector<std::string>> DBConfig;
	 NJHRShootUtil::ParseJsonPluginFile(configPath, DBConfig);
	
	 for (auto it = DBConfig.begin(); it != DBConfig.end();++it)
	 {
		 if ((*it).second.back() == "true")
		 {
			 std::vector<std::string> config = (*it).second;
			 config.pop_back();
			 return _p->_dataAccess.ConncetToDB(config);
		 }
	 }
	 ERROR_LOG << "δ�ҵ����ݿ�����";
	 return false;
}

const SoldierBaseInfoVec & NJHRDataManager::GetAllSoldiers() const
{
	return _p->_allSoldiers;
}

const UserPassWordTabVec & NJHRDataManager::GetAllUserPassword() const
{
	return _p->_allPassword;
}

bool NJHRDataManager::VerifyPassword(const std::string &userName, const std::string &passWord) const
{
	for (auto it = _p->_allPassword.begin(); it != _p->_allPassword.end();++it)
	{
		if (userName == (*it)->UserName && passWord == (*it)->PassWord)
		{
			return true;
		}
	}
	return false;
}

bool NJHRDataManager::BeginTransation()
{
	return _p->_dataAccess.beginTransation();
}

bool NJHRDataManager::CommitData()
{
	return _p->_dataAccess.commitData();
}

bool NJHRDataManager::RollBack()
{
	return _p->_dataAccess.rollBack();
}

void NJHRDataManager::InitData()
{
	_p->_dataAccess.GetAllSoldiers(_p->_allSoldiers);
	_p->_dataAccess.GetAllPassWord(_p->_allPassword);
	NJHRShootUtil::MakeUpOrganize(_p->_allSoldiers);
}

void NJHRDataManager::ClearData()
{
	_p->_allSoldiers.clear();
}
