#include "GeneralDoubleSpinBoxDelegate.h"

#include <QtWidgets/QDoubleSpinBox>

class GeneralDoubleSpinBoxDelegate::GeneralPrivate
{
public:
	GeneralPrivate()
		:minNum(0.),maxNum(99999.),step(1.)
	{

	}
public:
	double minNum;
	double maxNum;
	double step;
};

GeneralDoubleSpinBoxDelegate::GeneralDoubleSpinBoxDelegate(const double minNum, const double maxNum, const double step, QObject *parent)
	: QStyledItemDelegate(parent)
	,_p(new GeneralPrivate())
{
	_p->minNum = minNum;
	_p->maxNum = maxNum;
	_p->step = step;
}

GeneralDoubleSpinBoxDelegate::~GeneralDoubleSpinBoxDelegate()
{
	delete _p;
}

QWidget * GeneralDoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
	editor->setFrame(false);
	editor->setMinimum(_p->minNum);
	editor->setMaximum(_p->maxNum);
	editor->setSingleStep(_p->step);

	return editor;
}

void GeneralDoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	double value = index.model()->data(index, Qt::EditRole).toDouble();

	QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
	spinBox->setValue(value);
}

void GeneralDoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
	spinBox->interpretText();
	double value = spinBox->value();

	model->setData(index, value, Qt::EditRole);
}

void GeneralDoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	editor->setGeometry(option.rect);
}
