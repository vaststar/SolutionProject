#include "NJHRShootDataAccess.h"

#include <string>
#include <QtSql/QSqlError>

#include <LogLog/LogDefine.h>
#include <NJHRShootDataType/NJHRShootDataType.h>
#include <NJHRShootUtil/NJHRShootUtil.h>
#include <DataBaseOperate/DataBaseOperate.h>


static const std::string TablePrefix = "SJGLXT_";
static const std::string RYTableName = TablePrefix + "RENYUAN";	//人员
static const std::string GLTableName = TablePrefix + "GUANLI";	//管理
static const std::string CJTableName = TablePrefix + "DABAJILU";	//成绩
static const std::string DJTableName = TablePrefix + "DENGJI";	//等级
static const std::string CCTableName = TablePrefix + "CHANGCI";	//场次

static const std::map<std::string, std::string> RYTableKey={ {"BM","0"},{"MC","0"},{"XH","0"},{"DJ","1"} };
static const std::map<std::string, std::string> GLTableKey = { { "RYBM","0" },{ "DLMC","0" },{ "DDMM","0" } };
static const std::map<std::string, std::string> CJTableKey = { { "JLBM","0" },{ "RYBM","0" },{ "CCBM","0" },
															   { "DBCJ","2" },{"HXBL","2"},{"ZXBL","2"},{"DBSJ","0"} };
static const std::map<std::string, std::string> DJTableKey = { { "DJBM","0" },{ "DJMC","0" } };
static const std::map<std::string, std::string> CCTableKey = { { "CCBM","0" },{ "CCMC","0" },{ "SCSJXH","0" } };

class NJHRShootDataAccess::NJHRShootDataAccessPrivate
{
public:
	NJHRShootDataAccessPrivate()
	{

	}
public:
	DataBaseOperate _DB;
};

NJHRShootDataAccess::NJHRShootDataAccess()
	:_p(new NJHRShootDataAccessPrivate())
{
}

NJHRShootDataAccess::~NJHRShootDataAccess()
{
	delete _p;
}

bool NJHRShootDataAccess::ConncetToDB(const std::vector<std::string> &DBConfig)
{
	if (DBConfig.size() == 2)
	{
		//连接本地sqlite数据库
		try
		{
			_p->_DB.ConnectToDataBase(DBConfig.front().c_str(), DBConfig.back().c_str());
		}
		catch (const QSqlError & e)
		{
			ERROR_LOG << e.text().toStdString();
			return false;
		}
		NORMAL_LOG << "本地数据库 "<< DBConfig.front()<<" 连接成功!";
		return true;
	}
	else if (DBConfig.size() == 6)
	{
		try
		{
			_p->_DB.ConnectToDataBase(DBConfig[0].c_str(), atoi(DBConfig[1].c_str()), DBConfig[2].c_str(), DBConfig[3].c_str(),
									  DBConfig[4].c_str(), DBConfig[5].c_str());
		}
		catch (const QSqlError &e)
		{
			ERROR_LOG << e.text().toStdString();
			return false;
		}
		NORMAL_LOG << "远程数据库 ip:"<< DBConfig[0]<< " 端口: "<< DBConfig[1]<< " 数据库名: "<< DBConfig[2] <<" 连接成功!";
		return true;
	}
	ERROR_LOG << "无法连接数据库,配置文件出错!";
	return false;
}

bool NJHRShootDataAccess::GetAllSoldiers(SoldierBaseInfoVec &results)
{
	if (!_p->_DB.IsConnected()) return false;
	results.clear();

	std::vector<std::map<std::string, std::string>> queryRes;
	_p->_DB.QueryData(queryRes, RYTableName);
	//查询到所有人员
	std::for_each(queryRes.begin(), queryRes.end(), [this,&results](const std::map<std::string, std::string> &data) {
		SoldierBaseInfoPtr info = std::make_shared<SoldierBaseInfo>();
		ParseMapToSoldierBaseInfo(data, info);
		results.push_back(info);
	});
	return true;
}


bool NJHRShootDataAccess::GetAllPassWord(UserPassWordTabVec &results)
{
	if (!_p->_DB.IsConnected()) return false;
	results.clear();

	std::vector<std::map<std::string, std::string>> queryRes;
	_p->_DB.QueryData(queryRes, GLTableName);
	//所有密码表
	std::for_each(queryRes.begin(), queryRes.end(), [this, &results](const std::map<std::string, std::string> &data) {
		UserPassWordTabPtr info = std::make_shared<UserPassWordTab>();
		ParseMapToUserPassWordInfo(data, info);
		results.push_back(info);
	});
	return true;

}

void NJHRShootDataAccess::ParseMapToSoldierBaseInfo(const std::map<std::string, std::string> &parseMap, SoldierBaseInfoPtr &info)
{
	if (info == nullptr)
	{
		info = std::make_shared<SoldierBaseInfo>();
	}

	auto data = parseMap.end();

	data = parseMap.find("BM");
	info->ID = (*data).second;

	data = parseMap.find("MC");
	info->Name = (*data).second;

	data = parseMap.find("XH");
	info->Serial = (*data).second;

	data = parseMap.find("DJ");
	info->Level = static_cast<SoldierLevel>(atoi((*data).second.c_str()));

	data = parseMap.find("SJ");
	info->UperID = (*data).second;
}

void NJHRShootDataAccess::ParseMapToUserPassWordInfo(const std::map<std::string, std::string> &parseMap, UserPassWordTabPtr &info)
{
	if (info == nullptr)
	{
		info = std::make_shared<UserPassWordTab>();
	}

	auto data = parseMap.end();
	
	data = parseMap.find("RYBM");
	info->SoldierID = (*data).second;

	data = parseMap.find("DLMC");
	info->UserName = (*data).second;

	data = parseMap.find("DLMM");
	info->PassWord = (*data).second;
}

bool NJHRShootDataAccess::beginTransation()
{
	return _p->_DB.BeginTransation();
}

bool NJHRShootDataAccess::rollBack()
{
	return _p->_DB.RollBackOperate();
}

bool NJHRShootDataAccess::commitData()
{
	return _p->_DB.CommitOperate();
}

