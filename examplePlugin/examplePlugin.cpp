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
	return QStringLiteral("窗口插件").toStdString();
}

const std::string examplePlugin::getDescribe() const
{
	return QStringLiteral("窗口插件描述").toStdString();
}

const QIcon examplePlugin::getIcon()const
{
	return QIcon(QStringLiteral(":/Resources/缩小.png"));
}
