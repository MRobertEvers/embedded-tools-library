#pragma once

#include "IPool.h"

namespace Pool
{
template <typename T>
class IMultiPoolSource : public IPool<T>
{
public:
	virtual size_t objectSize() = 0;
};
}

