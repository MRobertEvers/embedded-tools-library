#pragma once

#include "MessagePtr.h"

namespace Actor
{
class IMessagePool
{
public:
	virtual MessagePtr acquire(size_t size) = 0;
};
}

