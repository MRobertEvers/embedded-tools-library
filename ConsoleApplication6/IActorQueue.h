#pragma once
#include "IMessage.h"

namespace Actor
{
// IMPORTANT! The actor queue must be blocking/signalling.
class IActorQueue
{
public:
	virtual void putMessage(IMessage* msg) = 0;
	virtual IMessage* getMessage() = 0;
};
}

