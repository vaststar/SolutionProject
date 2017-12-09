#ifndef EventBus_h__
#define EventBus_h__

#include "EventBus_global.h"

#include <functional>
#include "EventBusType.h"

/////////////////////////////////////////////////////////////////////////
///<summary>事件订阅机制(同个对象禁止订阅同一个事件多次)</summary>/////////////////////////////////
///
///<remarks>朱正天,2017.12.9。</remarks>//////////////////
//////////////////////////////////////////////////////////////////////////
class EVENTBUS_LIB_EXPORT EventBus
{
public:
	static EventBus *Instance();
public:
	///<summary> 推送事件(事件类型，参数指针) --朱正天,2017.12.9</summary>///
	void PostEvent(EventSpace::EventType event,void *const param);

	///<summary> 订阅事件（事件类型，订阅对象指针，订阅函数地址） --朱正天,2017.12.9</summary>///
	template<class ReceiveClass,typename Function>
	bool SubscribeEvent(EventSpace::EventType event, ReceiveClass receiver,Function function);

	///<summary> 取消订阅(事件类型，对象指针) --朱正天,2017.12.9</summary>///
	bool UnSubscribeEvent(EventSpace::EventType event, void *const receiver);

	///<summary> 取消类的事件订阅 --朱正天,2017.12.9</summary>///
	bool UnSubscribeEvent(void *const receiver);

	///<summary> 取消某个事件的订阅 --朱正天,2017.12.9</summary>///
	bool UnSubscribeEvent(EventSpace::EventType event);

	///<summary> 取消所有事件的订阅 --朱正天,2017.12.9</summary>///
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

