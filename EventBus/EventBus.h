#ifndef EventBus_h__
#define EventBus_h__

#include "EventBus_global.h"

#include <functional>
#include "EventBusType.h"

/////////////////////////////////////////////////////////////////////////
///<summary>�¼����Ļ���(ͬ�������ֹ����ͬһ���¼����)</summary>/////////////////////////////////
///
///<remarks>������,2017.12.9��</remarks>//////////////////
//////////////////////////////////////////////////////////////////////////
class EVENTBUS_LIB_EXPORT EventBus
{
public:
	static EventBus *Instance();
public:
	///<summary> �����¼�(�¼����ͣ�����ָ��) --������,2017.12.9</summary>///
	void PostEvent(EventSpace::EventType event,void *const param);

	///<summary> �����¼����¼����ͣ����Ķ���ָ�룬���ĺ�����ַ�� --������,2017.12.9</summary>///
	template<class ReceiveClass,typename Function>
	bool SubscribeEvent(EventSpace::EventType event, ReceiveClass receiver,Function function);

	///<summary> ȡ������(�¼����ͣ�����ָ��) --������,2017.12.9</summary>///
	bool UnSubscribeEvent(EventSpace::EventType event, void *const receiver);

	///<summary> ȡ������¼����� --������,2017.12.9</summary>///
	bool UnSubscribeEvent(void *const receiver);

	///<summary> ȡ��ĳ���¼��Ķ��� --������,2017.12.9</summary>///
	bool UnSubscribeEvent(EventSpace::EventType event);

	///<summary> ȡ�������¼��Ķ��� --������,2017.12.9</summary>///
	void UnsubscribeAll();
private:
	bool Subscribe(EventSpace::EventType event, void *const receiver,const std::function<void(void *const)> &function);
private:
	static EventBus *_mamage;
private:
	class EventBusPrivate;
	EventBusPrivate *_p;
private:
	EventBus();
	EventBus(const EventBus&);
	const EventBus &operator=(const EventBus&);
	~EventBus();
};

template<class ReceiveClass, typename Function>
bool EventBus::SubscribeEvent(EventSpace::EventType event, ReceiveClass receiver, Function function)
{
	return Subscribe(event,receiver,std::bind(function,receiver,std::placeholders::_1));
}

#endif // EventBus_h__

