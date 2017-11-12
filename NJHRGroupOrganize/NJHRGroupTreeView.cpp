#include "NJHRGroupTreeView.h"

#include <QtWidgets/QMenu>
#include <QFile>

#include <NJHRShootUtil/NJHRShootUtil.h>
#include <NJHRDataManager/NJHRDataManager.h>

class NJHRGroupTreeView::NJHRGroupTreeViewPrivate
{
public:
	NJHRGroupTreeViewPrivate()
		:_Menu(nullptr), _AddAction(nullptr), _EditAction(nullptr), _DeleteAction(nullptr)
	{

	}
public:
	QMenu * _Menu;//�Ҽ��˵�
	QAction * _AddAction;//��Ӱ�ť
	QAction * _EditAction;//�༭��ť
	QAction * _DeleteAction;//ɾ����ť

	QModelIndex _currentIndex;//��ǰ�Ҽ���index
};

NJHRGroupTreeView::NJHRGroupTreeView(QWidget *parent)
	: NJHRCommonTreeView(parent)
	,_p(new NJHRGroupTreeViewPrivate())
{
	InitView();
}

NJHRGroupTreeView::~NJHRGroupTreeView()
{
	delete _p;
}

void NJHRGroupTreeView::InitView()
{
	//������ʽ
	QFile fileExit("Config/styleSheet/NJHRGroupTreeView.qss");
	fileExit.open(QIODevice::ReadOnly);
	QString qss = fileExit.readAll();
	setStyleSheet(qss);

	//<summary> ���ñ��������� 2017/11/2--������ </summary> 
	SetViewData(NJHRDataManager::Instance()->GetAllSoldiers());

	//<summary> �Ҽ����� 2017/11/2--������ </summary> 
	setContextMenuPolicy(Qt::CustomContextMenu);

	InitMenu();

	connect(this, &QTreeView::customContextMenuRequested,this, &NJHRGroupTreeView::OnCustomContextMenuRequested);

	connect(_p->_AddAction, &QAction::triggered, this, &NJHRGroupTreeView::AddSoldierSlot);
	connect(_p->_EditAction, &QAction::triggered, this, &NJHRGroupTreeView::EditSoldierSlot);
	connect(_p->_DeleteAction, &QAction::triggered, this, &NJHRGroupTreeView::DelSoldierSlot);
}

void NJHRGroupTreeView::OnCustomContextMenuRequested(const QPoint &pos)
{
	_p->_currentIndex = indexAt(pos);

	_p->_EditAction->setEnabled(_p->_currentIndex.isValid());
	_p->_DeleteAction->setEnabled(_p->_currentIndex.isValid());
	
	_p->_Menu->exec(QCursor::pos());
}

void NJHRGroupTreeView::InitMenu()
{
	if (_p->_Menu) return;

	_p->_Menu = new QMenu(this);
	_p->_AddAction = new QAction(QStringLiteral("���"), _p->_Menu);
	_p->_Menu->addAction(_p->_AddAction);
	_p->_EditAction = new QAction(QStringLiteral("�޸�"), _p->_Menu);
	_p->_Menu->addAction(_p->_EditAction);
	_p->_DeleteAction = new QAction(QStringLiteral("ɾ��"), _p->_Menu);
	_p->_Menu->addAction(_p->_DeleteAction);
}

void NJHRGroupTreeView::AddSoldierSlot(bool checked)
{
	int row = model()->rowCount(_p->_currentIndex);
	model()->insertRow(row, _p->_currentIndex);
	//EditInfo(Index.child(row, 0), true);
}

void NJHRGroupTreeView::DelSoldierSlot(bool checked)
{
	model()->removeRow(_p->_currentIndex.row(), _p->_currentIndex.parent());
}

void NJHRGroupTreeView::EditSoldierSlot(bool checked)
{

}
