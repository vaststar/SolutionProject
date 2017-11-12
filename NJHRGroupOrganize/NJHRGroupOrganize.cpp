#include "NJHRGroupOrganize.h"

#include "NJHRLoginDialog.h"
#include "NJHRSystemMainWidget.h"

class NJHRGroupOrganize::NJHRGroupOrganizePrivate
{
public:
	NJHRGroupOrganizePrivate()
	{

	}
public:

};

NJHRGroupOrganize::NJHRGroupOrganize()
	:_p(new NJHRGroupOrganizePrivate())
{
	
}

NJHRGroupOrganize::~NJHRGroupOrganize()
{
	delete _p;
}

void NJHRGroupOrganize::startApp()
{
	NJHRLoginDialog *login = new NJHRLoginDialog();
	if (login->exec() == QDialog::Accepted)
	{
		NJHRSystemMainWidget *a = new NJHRSystemMainWidget();
		//a->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
		a->setWindowState(Qt::WindowMaximized);
		a->show();
	}
	
}
