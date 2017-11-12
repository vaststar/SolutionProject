#include "NJHRCommonTreeModel.h"

#include <QMimeData>
#include <QUuid>
#include <QStringList>
#include <QtGui/QBrush>
#include <QtGui/QPixmap>

#include <NJHRShootDataType/NJHRShootDataType.h>
#include <NJHRShootDataType/NJHRCommonTreeItem.h>

const QString BATTLETREEDATATYPE = "BattleTreeType";
Q_DECLARE_METATYPE(SoldierBaseInfoPtr)

class NJHRCommonTreeModel::NJHRCommonTreeModelPrivate
{
public:
	NJHRCommonTreeModelPrivate()
		:rootItem(new NJHRCommonTreeItem(QVariant(),nullptr))
		,dragedIndex(QModelIndex())
	{
	
	}
public:
	NJHRCommonTreeItem *rootItem;
	QModelIndex dragedIndex;//被拖动的index
};

NJHRCommonTreeModel::NJHRCommonTreeModel(QObject *parent)
	: QAbstractItemModel(parent)
	,_p(new NJHRCommonTreeModelPrivate())
{

}

NJHRCommonTreeModel::~NJHRCommonTreeModel()
{
	delete _p;
}

QVariant NJHRCommonTreeModel::data( const QModelIndex &index, int role ) const
{
	if(!index.isValid()) return QVariant();

	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
	case Qt::ToolTipRole:
		return QString::fromStdString(
			static_cast<NJHRCommonTreeItem*>(index.internalPointer())->data().value<SoldierBaseInfoPtr>()->Name);
	case Qt::ForegroundRole:
		
		break;
	case Qt::UserRole:
		if (SoldierBaseInfoPtr soldier = static_cast<NJHRCommonTreeItem*>(index.internalPointer())->data().value<SoldierBaseInfoPtr>())
		{
			return QVariant::fromValue<SoldierBaseInfoPtr>(soldier);
		}
		break;
	default:
		break;
	}
	return QVariant();
}

bool NJHRCommonTreeModel::setData( const QModelIndex &index, const QVariant &value,int role /*= Qt::EditRole*/ )
{
	if(!index.isValid()) return true;
	switch (role)
	{
	case Qt::EditRole:
		static_cast<NJHRCommonTreeItem*>(index.internalPointer())->data().value<SoldierBaseInfoPtr>()->Name = value.value<QString>().toStdString();
	default:
		break;
	}
	return true;
}

Qt::ItemFlags NJHRCommonTreeModel::flags( const QModelIndex &index ) const
{
	if (index.isValid())
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled |Qt::ItemIsEditable;
	}
	return Qt::NoItemFlags;
}

QVariant NJHRCommonTreeModel::headerData( int section, Qt::Orientation orientation,int role /*= Qt::DisplayRole*/ ) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			switch (section)
			{
			case 0:
				return QStringLiteral("编组信息");
			default:
				break;
			}
		}
		else if (role == Qt::TextAlignmentRole)
		{
			switch (section)
			{
			case 0:
				return Qt::AlignCenter;
			default:
				break;
			}
		}
		
	}
	return QVariant();
}

QModelIndex NJHRCommonTreeModel::index( int row, int column,const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	if (!hasIndex(row,column,parent)) return QModelIndex();

	NJHRCommonTreeItem *childItem = parent.isValid() ? static_cast<NJHRCommonTreeItem*>(parent.internalPointer())->GetChild(row):
													   _p->rootItem->GetChild(row);
	return childItem ? createIndex(row,column,childItem) : QModelIndex();
}

QModelIndex NJHRCommonTreeModel::parent( const QModelIndex &index ) const
{
	if(!index.isValid()) return QModelIndex();
	NJHRCommonTreeItem *parentItem = static_cast<NJHRCommonTreeItem*>(index.internalPointer())->GetParent();

	return parentItem == _p->rootItem ? QModelIndex() : createIndex(parentItem->RowInParent(),0,parentItem);
}

int NJHRCommonTreeModel::rowCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	NJHRCommonTreeItem *parentItem = parent.isValid() ? static_cast<NJHRCommonTreeItem*>(parent.internalPointer()) : _p->rootItem;
	return parentItem->childCount();
}

int NJHRCommonTreeModel::columnCount( const QModelIndex &parent /*= QModelIndex()*/ ) const
{
	return 1;
}

void NJHRCommonTreeModel::InitModelData( NJHRCommonTreeItem *data )
{
	beginResetModel();
	_p->rootItem = data;
	endResetModel();
}

QStringList NJHRCommonTreeModel::mimeTypes() const
{
	return QStringList()<<BATTLETREEDATATYPE;
}

Qt::DropActions NJHRCommonTreeModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction | Qt::IgnoreAction;
}

QMimeData * NJHRCommonTreeModel::mimeData( const QModelIndexList &indexes ) const
{
	QMimeData *mimeData = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData,QIODevice::WriteOnly);

	foreach(const QModelIndex &index,indexes)
	{
		if(!index.isValid()) continue;

		NJHRCommonTreeItem * indexItem = static_cast<NJHRCommonTreeItem*>(index.internalPointer());
		stream << reinterpret_cast<qint64>(indexItem);
		_p->dragedIndex = index;
		break;
	}
	mimeData->setData(BATTLETREEDATATYPE,encodedData);
	return mimeData;
}

bool NJHRCommonTreeModel::dropMimeData( const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent )
{
	if(action == Qt::IgnoreAction) return true;
	if(!data->hasFormat(BATTLETREEDATATYPE) || parent == _p->dragedIndex) return false;

	QByteArray encodedData = data->data(BATTLETREEDATATYPE);
	QDataStream stream(&encodedData,QIODevice::ReadOnly);
	qint64 dropedItemData = 0;
	stream>>dropedItemData;
	NJHRCommonTreeItem *dropItem = (NJHRCommonTreeItem*)dropedItemData;

	beginRemoveRows(_p->dragedIndex.parent(), static_cast<NJHRCommonTreeItem*>(_p->dragedIndex.internalPointer())->RowInParent(),
		static_cast<NJHRCommonTreeItem*>(_p->dragedIndex.internalPointer())->RowInParent() + 1);
	dropItem->GetParent()->removeChild(dropItem);
	endRemoveRows();

	NJHRCommonTreeItem *parentItem = parent.isValid() ? static_cast<NJHRCommonTreeItem*>(parent.internalPointer()) : _p->rootItem;
	beginInsertRows(parent, parentItem->childCount(), parentItem->childCount()+1);
	dropItem->SetParent(static_cast<NJHRCommonTreeItem*>(parent.internalPointer()));
	parentItem->appendChild(dropItem);
	endInsertRows();

	return true;

}

bool NJHRCommonTreeModel::removeRows( int row, int count, const QModelIndex & parent /*= QModelIndex()*/ )
{
	if(row + count > rowCount(parent)) return false;
	beginRemoveRows(parent,row,row+count);

	NJHRCommonTreeItem *parentItem = parent.isValid() ? static_cast<NJHRCommonTreeItem*>(parent.internalPointer()) : _p->rootItem;
	parentItem->removeChild(static_cast<NJHRCommonTreeItem*>(index(row,0,parent).internalPointer()));
	
	endRemoveRows();
	return true;
}

bool NJHRCommonTreeModel::insertRows( int row, int count, const QModelIndex & parent /*= QModelIndex()*/ )
{
	NJHRCommonTreeItem *parentItem = parent.isValid() ? static_cast<NJHRCommonTreeItem*>(parent.internalPointer()) : _p->rootItem;
	beginInsertRows(parent, parentItem->childCount(), parentItem->childCount()+1);

	SoldierBaseInfoPtr tempData = std::make_shared<SoldierBaseInfo>();
	tempData->Name = QStringLiteral("默认名称").toStdString();
	tempData->ID = QUuid::createUuid().toString().toStdString();
	tempData->Level = SoldierLevel_Normal;

	NJHRCommonTreeItem* childItem = new NJHRCommonTreeItem(QVariant::fromValue<SoldierBaseInfoPtr>(tempData), parentItem);
	parentItem->appendChild(childItem);

	endInsertRows();
	return true;
}
