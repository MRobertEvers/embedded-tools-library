#pragma once
#include "MessageHandle.h"


class IActorQueue
{
public:
	virtual void putMessage(MessageHandle msg) = 0;
	virtual MessageHandle getMessage() = 0;
};


