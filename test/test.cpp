// test.cpp : 定义控制台应用程序的入口点。
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
		ERROR_LOG << "连接陈公公";

	}
	std::vector<std::string> res{"12","艾丝凡啊","2","1","1"};
	a.BeginTransation();
	a.InsertData("sjglxt_renyuan", res);
	a.CommitOperate();
	std::vector<std::map<std::string, std::string>> f;
	a.QueryData(f, "sjglxt_renyuan");

	//std::map<std::string, std::string> valmap{ {"MC","的说法"},{"XH","5"} };
	//a.UpdateData("sjglxt_renyuan", "MC", "艾丝凡啊", valmap);
	//a.DeleteData("sjglxt_renyuan", "MC", "艾丝凡啊");
	system("pause");
}


void testLog()
{
	ERROR_LOG << "dasf我的";
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
	FacilityUtil::ParseJsonFile("D:\\后方防卫行动具体配置.config", aa);
}

#include <PluginCore/PluginManager.h>
void testPlugin()
{
	PluginManager::Instance()->startManager();
}

#include <QtCore/QAbstractTableModel>
#include <GeneralUI/DataTableModel.h>
#include <DataStructType/BaseItemData.h>
#include <QtWidgets/QTableView>
void testTable()
{
	DataTableModel *tableModel = new DataTableModel();
	std::vector<BaseItemDataPtr> dataVec;
	BaseItemDataPtr data = std::make_shared<BaseItemData>();
	data->SetName(QStringLiteral("侧侧").toStdString());
	dataVec.push_back(data);
	BaseItemDataPtr data1 = std::make_shared<BaseItemData>();
	data1->SetName(QStringLiteral("侧侧1").toStdString());
	dataVec.push_back(data1);
	BaseItemDataPtr data2 = std::make_shared<BaseItemData>();
	data2->SetName(QStringLiteral("侧侧2").toStdString());
	dataVec.push_back(data2);
	BaseItemDataPtr data3 = std::make_shared<BaseItemData>();
	data3->SetName(QStringLiteral("侧侧3").toStdString());
	dataVec.push_back(data3);
	tableModel->InitModelData(dataVec);
	QTableView *vi = new QTableView(0);
	vi->setModel(tableModel);
	vi->setDragEnabled(true);
	vi->setAcceptDrops(true);
	vi->setDragDropMode(QAbstractItemView::DragDrop);
	vi->show();

}

#include <GeneralUI/DataTreeItemModel.h>
#include <QtWidgets/QTreeView>
#include <DataStructType/BaseTreeItem.h>
Q_DECLARE_METATYPE(BaseItemDataPtr)
void testTree()
{
	DataTreeItemModel *treeModel = new DataTreeItemModel(0);
	QTreeView *treeView = new QTreeView();
	
	BaseTreeItem *root = new BaseTreeItem();

	BaseItemDataPtr data = std::make_shared<BaseItemData>();
	data->SetName(QStringLiteral("侧侧").toStdString());
	BaseTreeItem *item = new BaseTreeItem(QVariant::fromValue(data), root);
	root->appendChild(item);

	BaseItemDataPtr data1 = std::make_shared<BaseItemData>();
	data1->SetName(QStringLiteral("侧侧1").toStdString());
	BaseTreeItem *item1 = new BaseTreeItem(QVariant::fromValue(data1), item);
	item->appendChild(item1);
	
	BaseItemDataPtr data2 = std::make_shared<BaseItemData>();
	data2->SetName(QStringLiteral("侧侧2").toStdString());
	BaseTreeItem *item2 = new BaseTreeItem(QVariant::fromValue(data2), item);
	item->appendChild(item2);

	BaseItemDataPtr data3 = std::make_shared<BaseItemData>();
	data3->SetName(QStringLiteral("侧侧3").toStdString());
	BaseTreeItem *item3 = new BaseTreeItem(QVariant::fromValue(data3), item1);
	item1->appendChild(item3);

	treeModel->InitModelData(root);
	treeView->setModel(treeModel);

	treeView->setDragEnabled(true);
	treeView->setAcceptDrops(true);
	treeView->setDragDropMode(QAbstractItemView::DragDrop);
	treeView->show();
	
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
	//testWidget();
	//testUtil();
	//testPlugin();
	//testTable();
	testTree();
    return a.exec();
}

