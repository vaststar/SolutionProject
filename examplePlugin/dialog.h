#pragma once

#include <QtWidgets/QWidget>
namespace Ui { class dialog; };

class dialog : public QWidget
{
	Q_OBJECT

public:
	dialog(QWidget *parent = Q_NULLPTR);
	~dialog();

private:
	Ui::dialog *ui;
};
