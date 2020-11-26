#pragma once

namespace Pool
{
template <typename T>
class IPool
{
public:
	virtual T* acquire() = 0;
	virtual void release(T const* item) = 0;

	virtual int size() = 0;
	virtual int numAvailable() = 0;
};
}