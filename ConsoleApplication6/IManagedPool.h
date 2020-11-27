#pragma once
#include "TManaged.h"

namespace Pool::Managed
{
template <typename T, typename SmartPtr = TManaged<T>>
class IManagedPool
{
public:
	virtual SmartPtr acquire() = 0;
};
}
