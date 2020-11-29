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
template <typename T>
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

	Managed::TManagedMultiPoolPtr<T> acquire(size_t size)
	{
		return Managed::TManagedMultiPoolPtr{ &m_pool, size };
	};

private:
	TMultiPool<Managed::IManagedStorage<T>> m_pool;
};
}

