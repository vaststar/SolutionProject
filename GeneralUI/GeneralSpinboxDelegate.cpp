#include "GeneralSpinboxDelegate.h"

#include <QtWidgets/QSpinBox>

class GeneralSpinboxDelegate::GeneralPrivate
{
public:
	GeneralPrivate()
		:minNum(0),maxNum(99999),step(1)
	{

	}
public:
	int minNum;
	int maxNum;
	int step;
};

GeneralSpinboxDelegate::GeneralSpinboxDelegate(const int minNum, const int maxNum, const int step, QObject *parent)
	: QStyledItemDelegate(parent)
	,_p(new GeneralPrivate())
{
	_p->minNum = minNum;
	_p->maxNum = maxNum;
	_p->step = step;
}

GeneralSpinboxDelegate::~GeneralSpinboxDelegate()
{
	delete _p;
}

QWidget * GeneralSpinboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSpinBox *editor = new QSpinBox(parent);
	editor->setFrame(false);
	editor->setMinimum(_p->minNum);
	editor->setMaximum(_p->maxNum);
	editor->setSingleStep(_p->step);

	return editor;
}

void GeneralSpinboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int value = index.model()->data(index, Qt::EditRole).toInt();

	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void GeneralSpinboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->interpretText();
	int value = spinBox->value();

	model->setData(index, value, Qt::EditRole);
}

void GeneralSpinboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}

