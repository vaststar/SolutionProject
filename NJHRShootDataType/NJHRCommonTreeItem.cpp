#include "NJHRCommonTreeItem.h"

class NJHRCommonTreeItem::NJHRCommonTreeItemPrivate
{
public:
	NJHRCommonTreeItemPrivate()
		:_ItemData(QVariant())
	{

	}
public:
	QList<NJHRCommonTreeItem*> _ChildItems;//下级
	QVariant _ItemData;//数据
	NJHRCommonTreeItem* _ParentItem;
};

NJHRCommonTreeItem::NJHRCommonTreeItem(QVariant data ,NJHRCommonTreeItem *parent)
	:_p(new NJHRCommonTreeItemPrivate())
{
	_p->_ParentItem = parent ;
	_p->_ItemData = data ;
}


NJHRCommonTreeItem::~NJHRCommonTreeItem(void)
{
	qDeleteAll(_p->_ChildItems);
	delete _p;
}

void NJHRCommonTreeItem::appendChild( NJHRCommonTreeItem *child )
{
	_p->_ChildItems.append(child);
}

NJHRCommonTreeItem * NJHRCommonTreeItem::GetChild( int row )
{
	return _p->_ChildItems.at(row);
}

int NJHRCommonTreeItem::childCount() const
{
	return _p->_ChildItems.count();
}

QVariant NJHRCommonTreeItem::data() const
{
	return _p->_ItemData;
}

int NJHRCommonTreeItem::RowInParent() const
{
	return _p->_ParentItem ? _p->_ParentItem->_p->_ChildItems.indexOf(const_cast<NJHRCommonTreeItem*>(this)) : 0;
}

NJHRCommonTreeItem * NJHRCommonTreeItem::GetParent()
{
	return _p->_ParentItem;
}

void NJHRCommonTreeItem::SetParent( NJHRCommonTreeItem *parentItem )
{
	_p->_ParentItem = parentItem;
}

bool NJHRCommonTreeItem::removeChild( NJHRCommonTreeItem *childItem )
{
	return _p->_ChildItems.removeOne(childItem);
}

