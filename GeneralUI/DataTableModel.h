#ifndef DataTableModel_h__
#define DataTableModel_h__

#include "generalui_global.h"
#include <QAbstractTableModel>

#include <vector>
#include <memory>
/////////////////////////////////////////////////////////////////////////
///<summary>通用tableModel</summary>/////////////////////////////////
///
///<remarks>朱正天,2017.11.16。</remarks>//////////////////
//////////////////////////////////////////////////////////////////////////
class BaseItemData;
typedef std::shared_ptr<BaseItemData> BaseItemDataPtr;

class GENERALUI_EXPORT DataTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit DataTableModel(QObject *parent = nullptr);
	~DataTableModel();
public:
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
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
	void InitModelData(const std::vector<BaseItemDataPtr> data);
private:
	class DataTableModelPrivate;
	DataTableModelPrivate *_p;
};
#endif // DataTableModel_h__
