#ifndef QtBaseServer_h__
#define QtBaseServer_h__

#include "qtbaseserver_global.h"
#include <QTcpServer>
//////////////////////////////////////////////////////////////////////////
///<summary> 服务器类 </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class QTBASESERVER_EXPORT QtBaseServer : public QTcpServer
{
	Q_OBJECT
public:
	QtBaseServer(QObject *parent = 0);
	~QtBaseServer();
protected:
	virtual void incomingConnection(int socketDescriptor);
private:
	class QtBaseServerPrivate;
	QtBaseServerPrivate *_p;
};
#endif // QtBaseServer_h__
