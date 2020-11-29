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
		return m_pool.acquire();
	};

	virtual void release(Interface const* item) override
	{
		return m_pool.release(static_cast<T const*>(item));
	};

	virtual int size() override
	{
		return m_pool.size();
	};

	virtual int numAvailable() override
	{
		return m_pool.numAvailable();
	};

	virtual size_t objectSize() override
	{
		return SizeT;
	};
private:
	TStaticContiguousPool<T, Size> m_pool;
};
}

