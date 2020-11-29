#pragma once

#include "IPool.h"
#include "TManagedStorage.h"

namespace Pool::Managed
{
// TODO: Restrict to pointer types?
template <typename T>
class TManagedPtr
{
public:
	// TODO: I Don't like default constructor.
	TManagedPtr()
		: m_pool(nullptr), m_item(nullptr)
	{
	}

	TManagedPtr(IPool<TManagedStorage<T>>* pool)
		: m_pool(pool), m_item(pool->acquire())
	{
		if( m_item )
		{
			m_item->getCtrl()->incRef();
		}
	}

	TManagedPtr(const TManagedPtr& cpy)
	{
		m_item = cpy.m_item;
		m_pool = cpy.m_pool;

		if( m_item )
		{
			m_item->getCtrl()->incRef();
		}
	}

	~TManagedPtr()
	{
		if( m_item != nullptr && m_item->getCtrl()->count() > 0 )
		{
			auto count = m_item->getCtrl()->decRef();
			if( count == 0 )
			{
				m_pool->release(m_item);
			}
		}
	}

	T* operator->()
	{
		return m_item->getPtr();
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
