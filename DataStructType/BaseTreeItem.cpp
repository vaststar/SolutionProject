#include "BaseTreeItem.h"

class BaseTreeItem::BaseTreeItemPrivate
{
public:
	BaseTreeItemPrivate()
		:_ItemData(QVariant())
	{

	}
public:
	QList<BaseTreeItem*> _ChildItems;//下级
	QVariant _ItemData;//数据
	BaseTreeItem* _ParentItem;
};

BaseTreeItem::BaseTreeItem(QVariant data, BaseTreeItem *parent)
	:_p(new BaseTreeItemPrivate())
{
	_p->_ParentItem = parent;
	_p->_ItemData = data;
}


BaseTreeItem::~BaseTreeItem(void)
{
	qDeleteAll(_p->_ChildItems);
	delete _p;
}

void BaseTreeItem::appendChild(BaseTreeItem *child)
{
	_p->_ChildItems.append(child);
}

BaseTreeItem * BaseTreeItem::GetChild(int row)
{
	return _p->_ChildItems.at(row);
}

int BaseTreeItem::childCount() const
{
	return _p->_ChildItems.count();
}

QVariant BaseTreeItem::data() const
{
	return _p->_ItemData;
}

int BaseTreeItem::RowInParent() const
{
	return _p->_ParentItem ? _p->_ParentItem->_p->_ChildItems.indexOf(const_cast<BaseTreeItem*>(this)) : 0;
}

BaseTreeItem * BaseTreeItem::GetParent()
{
	return _p->_ParentItem;
}

void BaseTreeItem::SetParent(BaseTreeItem *parentItem)
{
	_p->_ParentItem = parentItem;
}

bool BaseTreeItem::removeChild(BaseTreeItem *childItem)
{
	return _p->_ChildItems.removeOne(childItem);
}

