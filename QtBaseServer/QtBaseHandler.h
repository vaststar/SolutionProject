#ifndef QtBaseHandler_h__
#define QtBaseHandler_h__

#include <QObject>
//////////////////////////////////////////////////////////////////////////
///<summary> 事件处理类 </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class QTcpSocket;
class QtBaseHandler : public QObject
{
	Q_OBJECT

public:
	explicit QtBaseHandler(QTcpSocket *socket, QObject *parent =  0);
	~QtBaseHandler();
private:
	void DealWithMessage(const std::map<std::string, std::string> &messageData);

public slots:
	void MessageReceived();
	void FinishConnected();
private:
	class QtBaseHandlerPrivate;
	QtBaseHandlerPrivate *_p;
};
#endif // QtBaseHandler_h__
