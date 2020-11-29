#pragma once
#include "TManagedPtr.h"

namespace Pool::Managed
{
template <typename T, typename SmartPtr = TManagedPtr<T>>
class IManagedPool
{
public:
	virtual SmartPtr acquire() = 0;
	virtual int allocated() = 0;
};
}
