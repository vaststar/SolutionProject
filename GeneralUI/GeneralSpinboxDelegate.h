#ifndef GeneralSpinboxDelegate_h__
#define GeneralSpinboxDelegate_h__

#include "generalui_global.h"
#include <QtWidgets/QStyledItemDelegate>
//////////////////////////////////////////////////////////////////////////
///<summary> 通用spinBox代理 </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class GENERALUI_EXPORT GeneralSpinboxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit GeneralSpinboxDelegate(const int minNum = 0,const int maxNum = 99999,const int step = 1,QObject *parent = 0);
	~GeneralSpinboxDelegate();
public:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
	class GeneralPrivate;
	GeneralPrivate *_p;
};
#endif // GeneralSpinboxDelegate_h__
