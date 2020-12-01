#pragma once
#include "IMultiPoolSource.h"
#include "TStaticContiguousPool.h"

namespace Pool
{
template <typename Interface, typename T, size_t Size, size_t SizeT = sizeof(T)>
class TStaticMultiPoolSource : public IMultiPoolSource<Interface>
{
public:
	virtual Interface* acquire() override
	{
		return pool_.acquire();
	};

	virtual void release(Interface const* item) override
	{
		return pool_.release(static_cast<T const*>(item));
	};

	virtual int size() override
	{
		return pool_.size();
	};

	virtual int numAvailable() override
	{
		return pool_.numAvailable();
	};

	virtual size_t objectSize() override
	{
		return SizeT;
	};
private:
	TStaticContiguousPool<T, Size> pool_;
};
}

