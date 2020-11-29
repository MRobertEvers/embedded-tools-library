#pragma once
#include "TMultiPool.h"
#include "TManagedStorage.h"

namespace Pool::Managed
{
template <typename T>
class TManagedMultiPoolPtr
{
public:
	TManagedMultiPoolPtr(IMultiPool<Managed::IManagedStorage<T>>* pool, size_t size)
		: m_pool(pool), m_item(pool->acquire(size)), m_size(size)
	{
		m_item->getCtrl()->incRef();
	};

	TManagedMultiPoolPtr(const TManagedMultiPoolPtr& cpy)
	{
		m_item = cpy.m_item;
		m_pool = cpy.m_pool;

		m_item->getCtrl()->incRef();
	};

	~TManagedMultiPoolPtr()
	{
		if( m_item->getCtrl()->count() > 0 )
		{
			auto count = m_item->getCtrl()->decRef();
			if( count == 0 )
			{
				m_pool->release(m_item, m_size);
			}
		}
	};

	T* operator->()
	{
		return &m_item->object;
	};

	bool ok()
	{
		return m_item != nullptr;
	};

private:
	IMultiPool<Managed::IManagedStorage<T>>* m_pool;
	Managed::IManagedStorage<T>* m_item;
	size_t m_size;
};
}

