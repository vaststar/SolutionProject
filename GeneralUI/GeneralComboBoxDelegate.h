#ifndef GeneralComboBoxDelegate_h__
#define GeneralComboBoxDelegate_h__

#include "generalui_global.h"
#include <QtWidgets/QStyledItemDelegate>

//////////////////////////////////////////////////////////////////////////
///<summary> ͨ��comboBox���� </summary>
///
///<remarks> ������,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/

class GENERALUI_EXPORT GeneralComboBoxDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	//<summary> ����ԴΪ ��ʾ��string����Ӧ��ö��ֵ��ɵ�vector 2017/11/9--������ </summary> 
	explicit GeneralComboBoxDelegate(std::vector<std::pair<std::string,int>> dataList = std::vector<std::pair<std::string, int>>(), 
									 QObject *parent = nullptr);
	~GeneralComboBoxDelegate();
public:
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
	class GeneralPrivate;
	GeneralPrivate *_p;
};
#endif // GeneralComboBoxDelegate_h__
