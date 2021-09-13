#pragma once
#include "IMultiPoolSource.h"
#include "TStaticContiguousPool.h"

namespace pvt
{
template <typename Interface, typename T, unsigned int Size, unsigned int SizeT = sizeof(T)>
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

	virtual unsigned int item_size() override
	{
		return SizeT;
	};
private:
	TStaticContiguousPool<T, Size> pool_;
};
}

