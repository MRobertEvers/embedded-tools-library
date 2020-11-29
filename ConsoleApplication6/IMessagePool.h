#pragma once

#include "MessagePtr.h"

namespace Actor
{
class IMessagePool
{
public:
	virtual MessagePtr acquire() = 0;
};
}

