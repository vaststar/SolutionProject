#include "DataBaseOperate.h"

#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

class DataBaseOperate::DataBaseOperatePrivate
{
public:
	DataBaseOperatePrivate()
	{

	}
public:
	QSqlDatabase dataBase;
};

DataBaseOperate::DataBaseOperate()
	:_p(new DataBaseOperatePrivate())
{
}

DataBaseOperate::~DataBaseOperate()
{
	delete _p;
}

bool DataBaseOperate::ConnectToDataBase(const std::string &ip, int port, const std::string &dbName, 
										const std::string &userName, const std::string &passWord, 
										const std::string &dbType /*= "QMYSQL"*/, const std::string &connectLabel /*= ""*/)
{
	_p->dataBase = QSqlDatabase::addDatabase(dbType.c_str(), connectLabel.c_str());
	_p->dataBase.setHostName(ip.c_str());
	_p->dataBase.setPort(port);
	_p->dataBase.setDatabaseName(dbName.c_str());
	_p->dataBase.setUserName(userName.c_str());
	_p->dataBase.setPassword(passWord.c_str());
	if (_p->dataBase.open())
	{
		_p->dataBase.exec("set names 'utf8'");
		return true;
	}
	throw _p->dataBase.lastError();
	return false;
}

bool DataBaseOperate::ConnectToDataBase(const std::string &dbName, const std::string &dbType /*= "QSQLITE"*/,
										const std::string &connectLabel/*=""*/)
{
	_p->dataBase = QSqlDatabase::addDatabase(dbType.c_str(), connectLabel.c_str());
	_p->dataBase.setDatabaseName(dbName.c_str());
	if (_p->dataBase.open())
	{
		_p->dataBase.exec("set names 'utf8'");
		return true;
	}
	throw _p->dataBase.lastError();
	return false;
}

bool DataBaseOperate::CloseConnect()
{
	if (_p->dataBase.isOpen())
	{
		_p->dataBase.close();
		return true;
	}
	return false;
}

bool DataBaseOperate::BeginTransation()
{
	if (!_p->dataBase.isOpen()) return false;
	return _p->dataBase.transaction();
}

bool DataBaseOperate::CommitOperate()
{
	if (!_p->dataBase.isOpen()) return false;
	return _p->dataBase.commit();
}

bool DataBaseOperate::RollBackOperate()
{
	if (!_p->dataBase.isOpen()) return false;
	return _p->dataBase.rollback();
}

bool DataBaseOperate::QueryData(std::vector<std::map<std::string, std::string>> &Result, const std::string &tableName, 
								const std::string &keyName/*=""*/, const std::string &value/*=""*/)
{
	if (!_p->dataBase.isOpen() || tableName.empty()) return false;

	Result.clear();

	std::string sqlStr = "select * from " + tableName;
	if (!keyName.empty())
	{
		sqlStr += " where " + keyName + " = " + value;
	}
	QSqlQuery sqlQuery = _p->dataBase.exec(sqlStr.c_str());
	ParseSqlQuery(sqlQuery, Result);
	return true;
}

bool DataBaseOperate::InsertData(const std::string &tableName, const std::vector<std::string> &values)
{
	if (!_p->dataBase.isOpen() || tableName.empty() || values.empty()) return false;

	std::string vals = "";
	for (auto it = values.begin(); it != values.end();++it)
	{
		vals += "'" + (*it) + "'" + ",";
	}
	vals.pop_back();

	std::string sqlStr = "insert into " + tableName + " values (" + vals + ")";

	_p->dataBase.exec(QString::fromLocal8Bit(sqlStr.c_str()));
	return true;
}

bool DataBaseOperate::DeleteData(const std::string &tableName, const std::string &keyName/*=""*/, const std::string &value/*=""*/)
{
	if (!_p->dataBase.isOpen() || tableName .empty() || keyName.empty() || value.empty()) return false;

	std::string sqlStr = "delete from " + tableName + " where " + keyName + " = '" + value + "'";
	_p->dataBase.exec(QString::fromLocal8Bit(sqlStr.c_str()));
	return true;
}

bool DataBaseOperate::UpdateData(const std::string &tableName, const std::string &keyName, const std::string &value, 
								 const std::map<std::string, std::string> &valueMaps)
{
	if (!_p->dataBase.isOpen() || tableName.empty() || keyName.empty() || value.empty() || valueMaps.empty()) return false;

	std::string vals = "";
	for (auto it = valueMaps.begin(); it != valueMaps.end();++it)
	{
		vals += (*it).first + "='" + (*it).second + "'" + ",";
	}
	vals.pop_back();

	std::string sqlStr = "update " + tableName + " set " + vals + " where " + keyName + " = '" + value + "'";
	_p->dataBase.exec(QString::fromLocal8Bit(sqlStr.c_str()));
	return true;
}

bool DataBaseOperate::ClearData(const std::string &tableName)
{
	if (!_p->dataBase.isOpen() || tableName.empty()) return false;

	std::string sqlStr = "delete from " + tableName;
	_p->dataBase.exec(QString::fromLocal8Bit(sqlStr.c_str()));
	return true;
}

bool DataBaseOperate::IsConnected() const
{
	return _p->dataBase.isOpen();
}

void DataBaseOperate::ParseSqlQuery(QSqlQuery sqlQuery, std::vector<std::map<std::string, std::string>> &Result)
{
	Result.clear();

	QSqlRecord sqlRecord = sqlQuery.record();
	int number = sqlRecord.count();

	while (sqlQuery.next())
	{
		std::map < std::string, std::string > oneQuery;
		for (int i = 0; i < number; ++i)
		{
			oneQuery[sqlRecord.fieldName(i).toStdString()] = sqlQuery.value(i).toString().toLocal8Bit();
		}
		Result.push_back(oneQuery);
	}
}
