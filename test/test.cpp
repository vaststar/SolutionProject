// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <LogLog/LogDefine.h>
#include <QtWidgets/QApplication>
#include <map>
#include <string>
#include <DataBaseOperate/DataBaseOperate.h>
void testDB()
{
	DataBaseOperate a;
	bool as = false;
	as = a.ConnectToDataBase("localhost", 3306, "zhuzhu", "root", "19910611","QMYSQL");
	//as = a.ConnectToDataBase("DB\\zhu", "QSQLITE");
	if (as)
	{
		ERROR_LOG << "���ӳ¹���";

	}
	std::vector<std::string> res{"12","��˿����","2","1","1"};
	a.BeginTransation();
	a.InsertData("sjglxt_renyuan", res);
	a.CommitOperate();
	std::vector<std::map<std::string, std::string>> f;
	a.QueryData(f, "sjglxt_renyuan");

	//std::map<std::string, std::string> valmap{ {"MC","��˵��"},{"XH","5"} };
	//a.UpdateData("sjglxt_renyuan", "MC", "��˿����", valmap);
	//a.DeleteData("sjglxt_renyuan", "MC", "��˿����");
	system("pause");
}


void testLog()
{
	ERROR_LOG << "dasf�ҵ�";
}



#include <WinBaseServer/WinBaseServer.h>
#include "MyObserver.h"
void testTCP()
{
	WinBaseServer server(5099, 50);
	server.startServer<MyObserver>();
}



#include <NJHRDataManager/NJHRDataManager.h>
void testDataManager()
{
	NJHRDataManager::Instance();
}


#include <NJHRGroupOrganize/NJHRGroupOrganize.h>
void testWidget()
{
	NJHRGroupOrganize *a = new NJHRGroupOrganize;
	a->startApp();
}

#include <FacilityUtil/FacilityUtil.h>
void testUtil()
{
	FacilityUtil::GetDateTime();
	std::map<std::string, std::vector<std::string>> aa;
	FacilityUtil::ParseJsonFile("D:\\�󷽷����ж���������.config", aa);
}

#include <PluginCore/PluginManager.h>
void testPlugin()
{
	PluginManager::Instance()->startManager();
}

#include <QtCore/QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
	//testDB();
	//testLog();
	//testTCP();
	//testDataAccess();
	//testDataManager();
	testWidget();
	//testUtil();
	//testPlugin();
    return a.exec();
}

