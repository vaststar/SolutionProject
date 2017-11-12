#include "QtBaseHandler.h"

#include <QTcpSocket>

class QtBaseHandler::QtBaseHandlerPrivate
{
public:
	QtBaseHandlerPrivate()
		:_socket(new QTcpSocket())
	{

	}
public:
	QTcpSocket * _socket;
};
QtBaseHandler::QtBaseHandler(QTcpSocket *socket, QObject *parent)
	: QObject(parent)
	, _p(new QtBaseHandlerPrivate())
{
	_p->_socket = socket;
	connect(_p->_socket, SIGNAL(readyRead()), this, SLOT(MessageReceived()));
	connect(_p->_socket, SIGNAL(disconnected()), this, SLOT(FinishConnected()));
}

QtBaseHandler::~QtBaseHandler()
{
	delete _p;
}

void QtBaseHandler::MessageReceived()
{
	QString message(_p->_socket->readAll());

	std::string gbkMessage = message.toStdString();

	std::map<std::string, std::string> resultMessage;
	//NJHRShootUtil::ParseJsonDataString(gbkMessage, resultMessage);
	DealWithMessage(resultMessage);

}

void QtBaseHandler::DealWithMessage(const std::map<std::string, std::string> &messageData)
{
	std::map<std::string, std::string> Data = messageData;
	
}

void QtBaseHandler::FinishConnected()
{
}
