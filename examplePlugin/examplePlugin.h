#ifndef EXAMPLEPLUGIN_H
#define EXAMPLEPLUGIN_H

#include "exampleplugin_global.h"

#include <PluginCore/PluginBase.h>

#include <QIcon>
class EXAMPLEPLUGIN_EXPORT examplePlugin :public PluginBase
{
public:
	examplePlugin();
	~examplePlugin();
public:
	virtual void InitialLize();
	virtual const std::string getName() const;
	virtual const std::string getDescribe() const;
	virtual const QIcon getIcon()const;

private:

};

#endif // EXAMPLEPLUGIN_H
