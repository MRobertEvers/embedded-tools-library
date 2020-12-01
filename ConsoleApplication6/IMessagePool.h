#pragma once

#include "IMessage.h"
#include "IMultiPool.h"

namespace Actor
{
class IMessagePool
{
public:
	virtual IMessage* acquire(size_t size) = 0;
	virtual void release(IMessage const* msg) = 0;
};
}

