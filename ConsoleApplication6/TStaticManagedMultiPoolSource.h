#pragma once
#include "IMultiPoolSource.h"
#include "TStaticContiguousPool.h"
#include "TManagedStorage.h"
#include "TStaticMultiPoolSource.h"

namespace Pool::Managed
{
template <typename Interface, typename T, size_t Size, size_t SizeT = sizeof(T)>
class TStaticManagedMultiPoolSource : public IManagedMultiPoolSource<Interface>
{
public:
	virtual IManagedStorage<Interface>* acquire() override
	{
		return (IManagedStorage<Interface>*)m_pool.acquire();
	};

	virtual void release(IManagedStorage<Interface> const* item) override
	{
		// This is normally NOT a safe conversion. We will run into issues if the returned item
		// is not from this pool. 
		// Example why
		// https://stackoverflow.com/questions/4605633/c-converting-a-container-to-a-container-of-different-yet-compatible-type
		return m_pool.release(static_cast<TManagedStorage<T> const*>((void*)item));
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
	TStaticContiguousPool<TManagedStorage<T>, Size> m_pool;
};
}

