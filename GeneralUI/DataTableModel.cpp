#include "DataTableModel.h"

#include <QMimeData>
#include <QDataStream>
#include <QUuid>
#include <DataStructType/BaseItemData.h>

static const QString BATTLETABLEDATATYPE = "BattleTableType";
Q_DECLARE_METATYPE(BaseItemDataPtr)

class DataTableModel::DataTableModelPrivate
{
public:
	DataTableModelPrivate()
	{

	}
public:
	std::vector<BaseItemDataPtr> _modelData;
	QModelIndexList dragedIndexList;
};

DataTableModel::DataTableModel(QObject *parent)
	: QAbstractTableModel(parent)
	,_p(new DataTableModelPrivate())
{
}

DataTableModel::~DataTableModel()
{
	delete _p;
}

QVariant DataTableModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid()) return QVariant();

	switch (role)
	{
	case Qt::EditRole:
	case Qt::DisplayRole:
	case Qt::ToolTipRole:
		return _p->_modelData[index.row()]->GetName().c_str();
	case Qt::ForegroundRole:
		break;
	case Qt::UserRole:
		return QVariant::fromValue<BaseItemDataPtr>(_p->_modelData[index.row()]);
		break;
	default:
		break;
	}
	return QVariant();
}

bool DataTableModel::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
	if (!index.isValid()) return true;
	switch (role)
	{
	case Qt::EditRole:
		_p->_modelData[index.row()]->SetName(value.value<QString>().toStdString());
	default:
		break;
	}
	return true;
}

Qt::ItemFlags DataTableModel::flags(const QModelIndex &index) const
{
	if (index.isValid())
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled ;
	}
	return Qt::ItemIsDropEnabled;
}

QVariant DataTableModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	if (orientation == Qt::Horizontal)
	{
		if (role == Qt::DisplayRole)
		{
			switch (section)
			{
			case 0:
				return QStringLiteral("Ãû³Æ");
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

int DataTableModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return _p->_modelData.size();
}

int DataTableModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}

bool DataTableModel::removeRows(int row, int count, const QModelIndex & parent /*= QModelIndex()*/)
{
	beginRemoveRows(parent, row, row + count);
	for (int i = 0; i < count; ++i)
	{
		_p->_modelData.erase(_p->_modelData.begin() + row);
	}
	endRemoveRows();
	return true;
}

bool DataTableModel::insertRows(int row, int count, const QModelIndex & parent /*= QModelIndex()*/)
{
	beginInsertRows(parent, row, row + count);
	for (int i = 0; i < count; ++i)
	{
		BaseItemDataPtr itemData = std::make_shared<BaseItemData>();
		itemData->SetName(QStringLiteral("Ä¬ÈÏÃû³Æ").toStdString());
		itemData->SetUUID(QUuid::createUuid().toString().toStdString());
		_p->_modelData.push_back(itemData);
	}
	endInsertRows();
	return true;
}

QStringList DataTableModel::mimeTypes() const
{
	return QStringList() << BATTLETABLEDATATYPE;
}

Qt::DropActions DataTableModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction | Qt::IgnoreAction;
}

QMimeData * DataTableModel::mimeData(const QModelIndexList &indexes) const
{
	QMimeData *mimeData = new QMimeData();
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	_p->dragedIndexList = indexes;
	std::stable_sort(_p->dragedIndexList.begin(), _p->dragedIndexList.end(), 
					 [](const QModelIndex &first, const QModelIndex &second)->bool {
		return first.row() < second.row();
	});
	foreach(const QModelIndex &index, _p->dragedIndexList)
	{
		if (!index.isValid()) continue;

		stream << reinterpret_cast<qint64>(&index);
	}
	mimeData->setData(BATTLETABLEDATATYPE, encodedData);
	return mimeData;
}

bool DataTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
	if (action == Qt::IgnoreAction) return true;
	if (!data->hasFormat(BATTLETABLEDATATYPE)) return false;

	QByteArray encodedData = data->data(BATTLETABLEDATATYPE);
	QDataStream stream(&encodedData, QIODevice::ReadOnly);

	std::vector<BaseItemDataPtr> dropIndexData;
	while (!stream.atEnd())
	{
		qint64 indexData;
		stream >> indexData;
		dropIndexData.push_back((*(reinterpret_cast<QModelIndex*>(indexData))).data(Qt::UserRole).value<BaseItemDataPtr>());
	}

	for (auto it = _p->dragedIndexList.rbegin(); it != _p->dragedIndexList.rend();++it)
	{
		beginRemoveRows(QModelIndex(),(*it).row(), (*it).row() + 1);
		_p->_modelData.erase(_p->_modelData.begin() + (*it).row());
		endRemoveRows();
	}
	_p->dragedIndexList.clear();

	for (auto it = dropIndexData.begin(); it != dropIndexData.end();++it)
	{
		beginInsertRows(QModelIndex(), rowCount(), rowCount() + 1);
		_p->_modelData.push_back(*it);
		endInsertRows();
	}
	
	return true;
}

void DataTableModel::InitModelData(const std::vector<BaseItemDataPtr> data)
{
	beginResetModel();
	_p->_modelData = data;
	endResetModel();
}
