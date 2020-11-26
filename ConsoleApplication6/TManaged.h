#pragma once
#include "ControlBlock.h"
#include "IPool.h"

namespace Pool::Managed
{
template <typename T>
class TManaged
{
public:
	TManaged(IPool<T>* pool, ControlBlock* control)
		: m_pool(pool), m_control(control), m_item(pool->acquire())
	{
		m_control->incRef();
	}

	TManaged(T* empty)
	{
	}

	TManaged(const TManaged& cpy)
	{
		m_item = cpy.m_item;
		m_pool = cpy.m_pool;
		m_control = cpy.m_pool;

		m_control->incRef();
	}

	~TManaged()
	{
		if( m_control->count() > 0 )
		{
			auto count = m_control->decRef();
			if( count == 0 )
			{
				m_pool->release(m_item);
			}
		}
	}

	T* operator->()
	{
		return m_item;
	}

	bool ok()
	{
		return m_item != nullptr;
	}

private:
	IPool<T>* m_pool;
	ControlBlock* m_control;
	T* m_item;
};
}
