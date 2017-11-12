#include "NJHRLoginDialog.h"
#include "ui_NJHRLoginDialog.h"

#include <QFile>
#include <QtWidgets/QMessageBox>
#include <NJHRDataManager/NJHRDataManager.h>

class NJHRLoginDialog::NJHRLoginDialogPrivate
{
public:
	NJHRLoginDialogPrivate()
	{

	}
public:
};

NJHRLoginDialog::NJHRLoginDialog(QWidget *parent)
	: QDialog(parent)
	,_p(new NJHRLoginDialogPrivate())
{
	ui = new Ui::NJHRLoginDialog();
	ui->setupUi(this);

	InitWidget();
}

NJHRLoginDialog::~NJHRLoginDialog()
{
	delete _p;
	delete ui; 
}

void NJHRLoginDialog::InitWidget()
{
	setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
	ui->lineEdit_password->setEchoMode(QLineEdit::Password);

	QFile fileExit("Config/styleSheet/NJHRLoginDialog.qss");
	fileExit.open(QFile::ReadOnly);
	QString qss = fileExit.readAll();
	setStyleSheet(qss);

	setAutoFillBackground(true);
	QPalette p;
	p.setBrush(QPalette::Window, QBrush(QPixmap(":/Resources/denglubeijing.png")));
	setPalette(p);

	connect(ui->pushButton_confirm, &QPushButton::clicked, this, &NJHRLoginDialog::OnConfirm);
	connect(ui->pushButton_cancel, &QPushButton::clicked, this, &NJHRLoginDialog::OnCancel);
}

void NJHRLoginDialog::OnConfirm()
{
	std::string userName = ui->lineEdit_username->text().toStdString();
	std::string passWord = ui->lineEdit_password->text().toStdString();

	if (!NJHRDataManager::Instance()->VerifyPassword(userName, passWord))
	{
		QMessageBox warningBox;
		warningBox.setWindowTitle(QStringLiteral("登录错误"));
		warningBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Dialog);
		warningBox.setText(QStringLiteral("用户名或密码错误"));
		warningBox.exec();
	}
	else
	{
		accept();
		close();
	}
}

void NJHRLoginDialog::OnCancel()
{
	rejected();
	close();
}
