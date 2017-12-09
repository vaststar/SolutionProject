#include "eventTestClass.h"

#include <iostream>
#include <EventBus/EventBus.h>

eventTestClass::eventTestClass()
{
	EventBus::Instance()->SubscribeEvent(EventSpace::FIRST_TYPE, this, &eventTestClass::test);
	int a = 4;
	EventBus::Instance()->PostEvent(EventSpace::FIRST_TYPE, &a);
}


eventTestClass::~eventTestClass()
{
}

void eventTestClass::test(void *param)
{
	int ff = *(int*)(param);
	std::cout << ff;
}
