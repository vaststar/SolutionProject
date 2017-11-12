#ifndef QtSocketThread_h__
#define QtSocketThread_h__

#include <QThread>
//////////////////////////////////////////////////////////////////////////
///<summary> 线程类 </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class QTcpSocket;
class QtSocketThread : public QThread
{
	Q_OBJECT

public:
	QtSocketThread(int socketDescriptor, QObject *parent);
	~QtSocketThread();
protected:
	virtual void run();
public:
	QTcpSocket *GetSocket()const;
private:
	class QtSocketThreadPrivate;
	QtSocketThreadPrivate *_p;
};
#endif // QtSocketThread_h__
