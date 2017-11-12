#ifndef DataTreeItemModel_h__
#define DataTreeItemModel_h__

#include "generalui_global.h"
#include <QAbstractItemModel>

//////////////////////////////////////////////////////////////////////////
///<summary> 通用树model </summary>
///
///<remarks> 朱正天,2017/11/2. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class BaseTreeItem;
class GENERALUI_EXPORT DataTreeItemModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	DataTreeItemModel(QObject *parent);
	~DataTreeItemModel();
public:
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	bool removeRows(int row, int count, const QModelIndex & parent = QModelIndex());
	bool insertRows(int row, int count, const QModelIndex & parent = QModelIndex());
public:
	QStringList mimeTypes()const;
	Qt::DropActions supportedDropActions() const;
	QMimeData * mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

public:
	//////////////////////////////////////////////////////////////////////////
	///<summary>  初始化编组树数据.</summary>
	///
	///<remarks> 朱正天,2017/1/8.</remarks>
	///////////////////////////////////////////////////////////////////////////
	void InitModelData(BaseTreeItem *data);
private:
	class DataTreeItemModelPrivate;
	DataTreeItemModelPrivate *_p;
};
#endif // DataTreeItemModel_h__
