#include "EventBus.h"

#include <mutex>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <memory>

static std::mutex mutex;
EventBus * EventBus::_mamage = nullptr;
EventBus * EventBus::Instance()
{
	if (nullptr == _mamage)
	{
		mutex.lock();
		if (nullptr == _mamage)
		{
			_mamage = new EventBus();
		}
		mutex.unlock();
	}
	return _mamage;
}

class EventBus::EventBusPrivate
{
public:
	EventBusPrivate()
	{

	}
public:
	std::map<EventSpace::EventType, std::vector<std::pair<void*, std::function<void(void*const)>>>> EventHandleMap;
};

EventBus::EventBus()
	:_p(new EventBusPrivate())
{
}

EventBus::~EventBus()
{
	delete _p;
}
void EventBus::PostEvent(EventSpace::EventType event, void *const param)
{
	std::map<EventSpace::EventType, std::vector<std::pair<void*, std::function<void(void*const)>>>>::const_iterator it = _p->EventHandleMap.find(event);
	if (it == _p->EventHandleMap.end()) return;

	std::for_each(it->second.begin(), it->second.end(), [param](const std::pair<void*, std::function<void(void*const)>>& data) {
		std::shared_ptr<std::thread> thread = std::make_shared<std::thread>([param,data]() {
			data.second(param);
		});
		thread->detach();
	});
}

bool EventBus::Subscribe(EventSpace::EventType event, void *const receiver, const std::function<void(void *const)> &function)
{
	if (nullptr == receiver) return false;
	std::map<EventSpace::EventType, std::vector<std::pair<void*, std::function<void(void*const)>>>>::iterator it = _p->EventHandleMap.find(event);
	if (it != _p->EventHandleMap.end())
	{
		auto iter = std::find_if(it->second.begin(), it->second.end(), 
								 [receiver](const std::pair<void*, std::function<void(void*const)>>& data) {
								 return receiver == data.first;								
								 });
		if (iter != it->second.end()) return false;
	}
	_p->EventHandleMap[event].push_back(std::make_pair(receiver, function));
	return true;
}

bool EventBus::UnSubscribeEvent(EventSpace::EventType event, void *const receiver)
{
	std::map<EventSpace::EventType, std::vector<std::pair<void*, std::function<void(void*const)>>>>::iterator it = _p->EventHandleMap.find(event);
	if (it == _p->EventHandleMap.end()) return false;
	if (nullptr == receiver)
	{
		it->second.clear();
	} 
	else
	{
		for (auto iter = it->second.begin(); iter != it->second.end();)
		{
			if (iter->first == receiver)
			{
				iter = it->second.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	return true;
}

bool EventBus::UnSubscribeEvent(void *const receiver)
{
	if (nullptr == receiver)
	{
		UnsubscribeAll();
		return true;
	}
	for (auto it = _p->EventHandleMap.begin(); it != _p->EventHandleMap.end();)
	{
		for (auto iter = it->second.begin(); iter != it->second.end();)
		{
			if (iter->first == receiver)
			{
				iter = it->second.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	return true;
}

bool EventBus::UnSubscribeEvent(EventSpace::EventType event)
{
	std::map<EventSpace::EventType, std::vector<std::pair<void*, std::function<void(void*const)>>>>::iterator it = _p->EventHandleMap.find(event);
	if (_p->EventHandleMap.end() == it) return false;
	_p->EventHandleMap.erase(it);
	return true;
}

void EventBus::UnsubscribeAll()
{
	_p->EventHandleMap.clear();
}


