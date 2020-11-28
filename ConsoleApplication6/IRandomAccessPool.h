#pragma once

#include "IPool.h"

namespace Pool
{
template <typename T>
class IRandomAccessPool : public IPool<T>
{
public:
	virtual int at(int i) = 0;
};

}

