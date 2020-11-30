#pragma once
#include "TMultiPool.h"
#include "TManagedStorage.h"
#include "TManagedMultiPoolPtr.h"
#include "ControlBlock.h"
#include "TArrayList.h"
#include "IManagedMultiPoolSource.h"
#include "TManagedMultiPoolPtr.h"

namespace Pool
{
template <typename T, typename SmartPtr = Managed::TManagedMultiPoolPtr<T>>
class TManagedMultiPool
{
public:
	template <size_t Size>
	TManagedMultiPool(
		std::array<IManagedMultiPoolSource<T>*, Size>* sources
	)
		: m_pool(sources)
	{

	};

	SmartPtr acquire(size_t size)
	{
		return SmartPtr{ &m_pool, size };
	};

private:
	TMultiPool<Managed::IManagedStorage<T>> m_pool;
};
}

