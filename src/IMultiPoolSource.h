#pragma once

#include "IPool.h"

namespace pvt
{
template <typename T>
class IMultiPoolSource : public IPool<T>
{
public:
	virtual unsigned int item_size() = 0;
};
}

