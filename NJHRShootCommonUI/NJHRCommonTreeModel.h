#ifndef NJHRCOMMONTREEMODEL_H
#define NJHRCOMMONTREEMODEL_H

#include "njhrshootcommonui_global.h"
#include <QAbstractItemModel>

//////////////////////////////////////////////////////////////////////////
///<summary> ͨ����ģ�� </summary>
///
///<remarks> ������,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////

class NJHRCommonTreeItem;
class NJHRSHOOTCOMMONUI_EXPORT NJHRCommonTreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit NJHRCommonTreeModel(QObject *parent = 0);
	virtual ~NJHRCommonTreeModel();

public:
	QVariant data(const QModelIndex &index, int role) const;
	bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	bool removeRows( int row, int count, const QModelIndex & parent = QModelIndex());
	bool insertRows ( int row, int count, const QModelIndex & parent = QModelIndex());
public:
	QStringList mimeTypes()const;
	Qt::DropActions supportedDropActions() const;
	QMimeData * mimeData(const QModelIndexList &indexes) const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

public:
	//////////////////////////////////////////////////////////////////////////
	///<summary>  ��ʼ������������.</summary>
	///
	///<remarks> ������,2017/1/8.</remarks>
	///////////////////////////////////////////////////////////////////////////
	void InitModelData(NJHRCommonTreeItem *data);
private:
	class NJHRCommonTreeModelPrivate;
	NJHRCommonTreeModelPrivate *_p;
	
};

#endif // NJHRCOMMONTREEMODEL_H
