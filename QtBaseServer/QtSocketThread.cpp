#include "QtSocketThread.h"

#include <QTcpSocket>

class QtSocketThread::QtSocketThreadPrivate
{
public:
	QtSocketThreadPrivate()
		:socket(new QTcpSocket())
		, socketDescriptor(0)
	{

	}
public:
	int socketDescriptor;
	QTcpSocket *socket;
};

QtSocketThread::QtSocketThread(int socketDescriptor, QObject *parent)
	: QThread(parent)
	, _p(new QtSocketThreadPrivate())
{
	_p->socketDescriptor = socketDescriptor;
}

QtSocketThread::~QtSocketThread()
{
	delete _p;
}

QTcpSocket * QtSocketThread::GetSocket() const
{
	return _p->socket;
}

void QtSocketThread::run()
{
	_p->socket->setSocketDescriptor(_p->socketDescriptor);
	QThread::run();
}
