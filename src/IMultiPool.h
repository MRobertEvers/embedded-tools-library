#pragma once

namespace pvt
{
template <typename T>
class IMultiPool
{
public:	
	virtual T* acquire(unsigned int size) = 0;
	virtual void release(T const* item, unsigned int size) = 0;
};
}

