#include "DataTreeItemModel.h"

#include <QMimeData>
#include <QUuid>
#include <QStringList>
#include <QtGui/QBrush>
#include <QtGui/QPixmap>

#include <DataStructType/BaseItemData.h>
#include <DataStructType/BaseTreeItem.h>

static const QString BATTLETREEDATATYPE = "BattleTreeType";
Q_DECLARE_METATYPE(BaseItemDataPtr)

class DataTreeItemModel::DataTreeItemModelPrivate
{
public:
	DataTreeItemModelPrivate()
		:rootItem(new BaseTreeItem(QVariant(), nullptr))
		, dragedIndex(QModelIndex())
	{

	}
public:
	BaseTreeItem *rootItem;
	QModelIndex dragedIndex;//被拖动的index
};

DataTreeItemModel::DataTreeItemModel(QObject *parent)
	: QAbstractItemModel(parent)
	, _p(new DataTreeItemModelPrivate())
{
}

DataTreeItemModel::~DataTreeItemModel()
{
	delete _p;
}

QVariant DataTreeItemModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();

	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
	case Qt::ToolTipRole:
		return QString::fromStdString(
			static_cast<BaseTreeItem*>(index.internalPointer())->data().value<BaseItemDataPtr>()->GetName());
	case Qt::ForegroundRole:

		break;
	case Qt::UserRole:
		if (BaseItemDataPtr soldier = static_cast<BaseTreeItem*>(index.internalPointer())->data().value<BaseItemDataPtr>())
		{
			return QVariant::fromValue<BaseItemDataPtr>(soldier);
		}
		break;
	default:
		break;
	}
	return QVariant();
}

bool DataTreeItemModel::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
	if (!index.isValid()) return true;
	switch (role)
	{
	case Qt::EditRole:
		static_cast<BaseTreeItem*>(index.internalPointer())->data().value<BaseItemDataPtr>()->SetName(value.value<QString>().toStdString());
	default:
		break;
	}
	return true;
}

Qt::ItemFlags DataTreeItemModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
	}
	return Qt::NoItemFlags;
}

QVariant DataTreeItemModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
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

QModelIndex DataTreeItemModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
{
	if (!hasIndex(row, column, parent)) return QModelIndex();

	BaseTreeItem *childItem = parent.isValid() ? static_cast<BaseTreeItem*>(parent.internalPointer())->GetChild(row) : _p->rootItem->GetChild(row);
	return childItem ? createIndex(row, column, childItem) : QModelIndex();
}

QModelIndex DataTreeItemModel::parent(const QModelIndex &index) const
{
	if (!index.isValid()) return QModelIndex();
	BaseTreeItem *parentItem = static_cast<BaseTreeItem*>(index.internalPointer())->GetParent();

	return parentItem == _p->rootItem ? QModelIndex() : createIndex(parentItem->RowInParent(), 0, parentItem);
}

int DataTreeItemModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	BaseTreeItem *parentItem = parent.isValid() ? static_cast<BaseTreeItem*>(parent.internalPointer()) : _p->rootItem;
	return parentItem->childCount();
}

int DataTreeItemModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}

void DataTreeItemModel::InitModelData(BaseTreeItem *data)
{
	beginResetModel();
	_p->rootItem = data;
	endResetModel();
}

QStringList DataTreeItemModel::mimeTypes() const
{
	return QStringList() << BATTLETREEDATATYPE;
}

Qt::DropActions DataTreeItemModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction | Qt::IgnoreAction;
}

QMimeData * DataTreeItemModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach(const QModelIndex &index, indexes)
	{
		if (!index.isValid()) continue;

		BaseTreeItem * indexItem = static_cast<BaseTreeItem*>(index.internalPointer());
		stream << reinterpret_cast<qint64>(indexItem);
		_p->dragedIndex = index;
		break;
	}
	mimeData->setData(BATTLETREEDATATYPE, encodedData);
	return mimeData;
}

bool DataTreeItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
	if (action == Qt::IgnoreAction) return true;
	if (!data->hasFormat(BATTLETREEDATATYPE)) return false;

	QByteArray encodedData = data->data(BATTLETREEDATATYPE);
	QDataStream stream(&encodedData, QIODevice::ReadOnly);
	qint64 dropedItemData = 0;
	stream >> dropedItemData;
	BaseTreeItem *dropItem = (BaseTreeItem*)dropedItemData;

	beginRemoveRows(_p->dragedIndex.parent(), static_cast<BaseTreeItem*>(_p->dragedIndex.internalPointer())->RowInParent(),
		static_cast<BaseTreeItem*>(_p->dragedIndex.internalPointer())->RowInParent() + 1);
	dropItem->GetParent()->removeChild(dropItem);
	endRemoveRows();

	BaseTreeItem *parentItem = parent.isValid() ? static_cast<BaseTreeItem*>(parent.internalPointer()) : _p->rootItem;
	beginInsertRows(parent, parentItem->childCount(), parentItem->childCount() + 1);
	dropItem->SetParent(static_cast<BaseTreeItem*>(parent.internalPointer()));
	parentItem->appendChild(dropItem);
	endInsertRows();

	return true;
}

bool DataTreeItemModel::removeRows(int row, int count, const QModelIndex & parent /*= QModelIndex()*/)
{
	if (row + count > rowCount(parent)) return false;
	beginRemoveRows(parent, row, row + count);

	BaseTreeItem *parentItem = parent.isValid() ? static_cast<BaseTreeItem*>(parent.internalPointer()) : _p->rootItem;
	parentItem->removeChild(static_cast<BaseTreeItem*>(index(row, 0, parent).internalPointer()));

	endRemoveRows();
	return true;
}

bool DataTreeItemModel::insertRows(int row, int count, const QModelIndex & parent /*= QModelIndex()*/)
{
	BaseTreeItem *parentItem = parent.isValid() ? static_cast<BaseTreeItem*>(parent.internalPointer()) : _p->rootItem;

	beginInsertRows(parent, parentItem->childCount(), parentItem->childCount() + 1);

	BaseItemDataPtr tempData = std::make_shared<BaseItemData>();
	tempData->SetName(QStringLiteral("默认名称").toStdString());
	tempData->SetUUID(QUuid::createUuid().toString().toStdString());

	BaseTreeItem* childItem = new BaseTreeItem(QVariant::fromValue<BaseItemDataPtr>(tempData), parentItem);
	parentItem->appendChild(childItem);

	endInsertRows();
	return true;
}
