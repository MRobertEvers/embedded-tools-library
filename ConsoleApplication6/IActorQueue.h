#pragma once
#include "MessageHandle.h"

namespace Actor
{
// IMPORTANT! The actor queue must be blocking/signalling.
class IActorQueue
{
public:
	virtual void putMessage(MessageHandle msg) = 0;
	virtual MessageHandle getMessage() = 0;
};
}

