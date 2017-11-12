#ifndef GeneralDoubleSpinBoxDelegate_h__
#define GeneralDoubleSpinBoxDelegate_h__

#include "generalui_global.h"
#include <QtWidgets/QStyledItemDelegate>
//////////////////////////////////////////////////////////////////////////
///<summary> 通用doubleSpinBox代理 </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class GeneralDoubleSpinBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit GeneralDoubleSpinBoxDelegate(const double minNum = 0., const double maxNum = 99999., const double step = 1., QObject *parent = nullptr);
	~GeneralDoubleSpinBoxDelegate();
public:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
private:
	class GeneralPrivate;
	GeneralPrivate *_p;
};
#endif // GeneralDoubleSpinBoxDelegate_h__
