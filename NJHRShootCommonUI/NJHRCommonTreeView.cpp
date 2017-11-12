#include "NJHRCommonTreeView.h"

#include <NJHRShootUtil/NJHRShootUtil.h>

#include "NJHRCommonTreeModel.h"


class NJHRCommonTreeView::NJHRCommonTreeViewPrivate
{
public:
	NJHRCommonTreeViewPrivate()
		:treeModel(new NJHRCommonTreeModel())
	{
	
	}
public:
	NJHRCommonTreeModel *treeModel;
};

NJHRCommonTreeView::NJHRCommonTreeView(QWidget *parent)
	: QTreeView(parent)
	,_p(new NJHRCommonTreeViewPrivate())
{
	InitView();
}

NJHRCommonTreeView::~NJHRCommonTreeView()
{
	delete _p;
}

void NJHRCommonTreeView::InitView()
{
	setModel(_p->treeModel);
	setDragEnabled(true);
	viewport()->setAcceptDrops(true);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::DragDrop);
}

void NJHRCommonTreeView::SetViewData( const SoldierBaseInfoVec &data )
{
	NJHRCommonTreeItem *rootItem = nullptr;
	NJHRShootUtil::ConvertOrganizedSoldierToTreeItem(data,rootItem);
	_p->treeModel->InitModelData(rootItem);
	expandAll();
}
