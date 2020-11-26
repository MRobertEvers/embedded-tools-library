#pragma once

namespace Pool
{
template <typename T>
class IPoolResource
{
public:
	virtual T* allocate() = 0;
	virtual void free(T const* item) = 0;
};
}