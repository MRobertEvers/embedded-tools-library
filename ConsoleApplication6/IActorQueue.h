#pragma once
#include "MessagePtr.h"

namespace Actor
{
// IMPORTANT! The actor queue must be blocking/signalling.
class IActorQueue
{
public:
	virtual void putMessage(MessagePtr msg) = 0;
	virtual MessagePtr getMessage() = 0;
};
}

