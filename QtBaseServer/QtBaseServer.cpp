#include "QtBaseServer.h"

#include <QTcpSocket>
#include "QtBaseHandler.h"
#include "QtSocketThread.h"

class QtBaseServer::QtBaseServerPrivate
{
public:
	QtBaseServerPrivate()
	{

	}
public:

};

QtBaseServer::QtBaseServer(QObject *parent)
	: QTcpServer(parent)
	, _p(new QtBaseServerPrivate())
{

}

QtBaseServer::~QtBaseServer()
{
	delete _p;
}

void QtBaseServer::incomingConnection(int socketDescriptor)
{
	QtSocketThread *thread = new QtSocketThread(socketDescriptor, this);
	QtBaseHandler* handler = new QtBaseHandler(thread->GetSocket());

	connect(thread, &QThread::finished, thread, &QThread::deleteLater);
	handler->moveToThread(thread);
	thread->start();
}
