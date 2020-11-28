#pragma once
#include "ControlBlock.h"
#include "IPool.h"
#include "TManagedStorage.h"

namespace Pool::Managed
{
// TODO: Restrict to pointer types?
template <typename T>
class TManaged
{
public:
	// TODO: I Don't like default constructor.
	TManaged()
		: m_pool(nullptr), m_item(nullptr)
	{
	}

	TManaged(IPool<TManagedStorage<T>>* pool)
		: m_pool(pool), m_item(pool->acquire())
	{
		m_item->control.incRef();
	}

	TManaged(const TManaged& cpy)
	{
		m_item = cpy.m_item;
		m_pool = cpy.m_pool;

		m_item->control.incRef();
	}

	~TManaged()
	{
		if( m_item->control.count() > 0 )
		{
			auto count = m_item->control.decRef();
			if( count == 0 )
			{
				m_pool->release(m_item);
			}
		}
	}

	T* operator->()
	{
		return &m_item->object;
	}

	T operator*()
	{
		return &m_item->object;
	}

	bool ok()
	{
		return m_item != nullptr;
	}

private:
	IPool<TManagedStorage<T>>* m_pool;
	TManagedStorage<T>* m_item;
};
}
