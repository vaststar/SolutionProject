#include "exampleplugin.h"

#include "dialog.h"
#include <QString>

#include <PluginCore/PluginRegister.h>
REGISTER_PLUGIN(examplePlugin);

examplePlugin::examplePlugin()
{

}

examplePlugin::~examplePlugin()
{

}

void examplePlugin::InitialLize()
{
	dialog *dia = new dialog();
	dia->show();
}

const std::string examplePlugin::getName() const
{
	return QStringLiteral("���ڲ��").toStdString();
}

const std::string examplePlugin::getDescribe() const
{
	return QStringLiteral("���ڲ������").toStdString();
}

const QIcon examplePlugin::getIcon()const
{
	return QIcon(QStringLiteral(":/Resources/��С.png"));
}
