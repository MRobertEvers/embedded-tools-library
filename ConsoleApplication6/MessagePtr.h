#pragma once
#include "TManagedMultiPoolPtr.h"
#include "IMessage.h"

namespace Actor
{
class MessagePtr
{
public:
	MessagePtr(IMessage* msg)
		: m_pool(nullptr), m_size(0)
	{
		m_item.staticMsg = msg;
	}

	MessagePtr(Pool::TMultiPool<Pool::Managed::IManagedStorage<IMessage>>* pool, size_t size)
		: m_pool(pool), m_size(size)
	{
		m_item.poolMsg = pool->acquire(size);
		if( ok() && m_pool != nullptr )
		{
			m_item.poolMsg->getCtrl()->incRef();
		}
	};

	MessagePtr(const MessagePtr& cpy)
	{
		m_item = cpy.m_item;
		m_pool = cpy.m_pool;
		m_size = cpy.m_size;

		if( ok() && m_pool != nullptr )
		{
			m_item.poolMsg->getCtrl()->incRef();
		}
	};

	~MessagePtr()
	{
		if( m_pool != nullptr && m_item.poolMsg != nullptr && m_item.poolMsg->getCtrl()->count() > 0 )
		{
			auto count = m_item.poolMsg->getCtrl()->decRef();
			if( count == 0 )
			{
				m_pool->release(m_item.poolMsg, m_size);
			}
		}
	};

	IMessage* operator->()
	{
		return m_pool != nullptr ? m_item.poolMsg->getPtr() : m_item.staticMsg;
	};

	bool ok()
	{
		return m_item.poolMsg != nullptr || m_item.staticMsg != nullptr;
	};

	MessagePtr clone()
	{
		MessagePtr item = MessagePtr{ m_pool, m_size };

		memcpy(item.operator->(), m_item.poolMsg->getPtr(), sizeof(*m_item.poolMsg->getPtr()));

		return item;
	}
private:
	Pool::TMultiPool<Pool::Managed::IManagedStorage<IMessage>>* m_pool;

	union
	{
		Pool::Managed::IManagedStorage<IMessage>* poolMsg;
		IMessage* staticMsg;
	} m_item;

	size_t m_size;
};
}

