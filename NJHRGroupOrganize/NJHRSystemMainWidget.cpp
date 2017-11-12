#include "NJHRSystemMainWidget.h"
#include "ui_NJHRSystemMainWidget.h"

#include <QFile>
#include "NJHRGroupTreeView.h"

class NJHRSystemMainWidget::NJHRSystemMainWidgetPrivate
{
public:
	NJHRSystemMainWidgetPrivate()
		:_groupView(new NJHRGroupTreeView())
	{

	}
public:
	NJHRGroupTreeView *_groupView;
};

NJHRSystemMainWidget::NJHRSystemMainWidget(QWidget *parent)
	: QWidget(parent)
	,_p(new NJHRSystemMainWidgetPrivate())
{
	ui = new Ui::NJHRSystemMainWidget();
	ui->setupUi(this);
	InitWidget();
}

NJHRSystemMainWidget::~NJHRSystemMainWidget()
{
	delete _p;
	delete ui;
}

void NJHRSystemMainWidget::InitWidget()
{
	QFile fileExit("Config/styleSheet/NJHRSystemMainWidget.qss");
	fileExit.open(QFile::ReadOnly);
	QString qss = fileExit.readAll();
	setStyleSheet(qss);

	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(QPalette::Window, QBrush(QPixmap(":/Resources/denglubeijing.png")));
	setPalette(p);

	ui->scrollArea_group->setWidget(_p->_groupView);

	connect(ui->pushButton_exit, &QPushButton::clicked, this, &NJHRSystemMainWidget::OnExit);
}

void NJHRSystemMainWidget::OnExit()
{
	close();
}
