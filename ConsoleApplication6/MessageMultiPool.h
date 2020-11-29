#pragma once
#include "IPool.h"
#include "IMessage.h"
#include "TMessage.h"
#include "TArrayList.h"
#include "TManagedContiguousPool.h"
#include "ControlBlock.h"

class MultiPoolElement
{
public:
	MultiPoolElement(Actor::IMessage* msg, int id, int index )
		: message(msg), poolId(id), poolIndex(index)
	{

	}

	Actor::IMessage* message;
	int poolId;
	int poolIndex;
};

class MultiPoolElementStorage
{
public:
	MultiPoolElementStorage(Actor::IMessage* msg, int id, int index)
		: object(msg, id, index)
	{

	}

	MultiPoolElement object;
	Pool::Managed::ControlBlock control;
};


class MessagePool
{
	using SmallMessage = Actor::TMessage<4>;
	using SmallMessagePtr = Pool::Managed::TManagedPtr<SmallMessage>;
	using NormalMessage = Actor::TMessage<16>;
	using NormalMessagePtr = Pool::Managed::TManagedPtr<NormalMessage>;
	using BigMessage = Actor::TMessage<32>;
	using BigMessagePtr = Pool::Managed::TManagedPtr<BigMessage>;
public:
	MessagePool()
		: smallpool(&smallbuf), smallptrs(&smallptrsbuf), 
		mediumpool(&mediumbuf), mediumptrs(&mediumptrsbuf),
		largepool(&largebuf), largeptrs(&largeptrsbuf),
		elemlist(&elembuf)
	{

	};

	MultiPoolElementStorage* acquire(size_t size);
	void release(MultiPoolElementStorage const* item);
	int size();

private:
	Pool::Resource::TManagedContiguousPoolBuffer<SmallMessage, 120> smallbuf;
	Pool::Managed::TManagedContiguousPool<SmallMessage> smallpool;
	TArrayListBuffer<SmallMessagePtr, 120> smallptrsbuf;
	TArrayList<SmallMessagePtr> smallptrs;

	Pool::Resource::TManagedContiguousPoolBuffer<NormalMessage, 24> mediumbuf;
	Pool::Managed::TManagedContiguousPool<NormalMessage> mediumpool;
	TArrayListBuffer<NormalMessagePtr, 24> mediumptrsbuf;
	TArrayList<NormalMessagePtr> mediumptrs;

	Pool::Resource::TManagedContiguousPoolBuffer<BigMessage, 2> largebuf;
	Pool::Managed::TManagedContiguousPool<BigMessage> largepool;
	TArrayListBuffer<BigMessagePtr, 2> largeptrsbuf;
	TArrayList<BigMessagePtr> largeptrs;
	
	TArrayListBuffer<MultiPoolElementStorage, 146> elembuf;
	TArrayList<MultiPoolElementStorage> elemlist;
};


class ManagedMessagePtr
{
public:
	ManagedMessagePtr(MessagePool* pool, size_t size)
		: m_pool(pool), m_item(pool->acquire(size)), m_size(size)
	{
		m_item->control.incRef();
	}

	ManagedMessagePtr(const ManagedMessagePtr& cpy)
	{
		m_item = cpy.m_item;
		m_pool = cpy.m_pool;
		m_size = cpy.m_size;

		m_item->control.incRef();
	}

	~ManagedMessagePtr()
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

	ManagedMessagePtr cloneMessage()
	{
		return ManagedMessagePtr{ m_pool, m_size };
	}

	Actor::IMessage* operator->()
	{
		return m_item->object.message;
	}

	bool ok()
	{
		return m_item != nullptr;
	}

private:
	MessagePool* m_pool;
	MultiPoolElementStorage* m_item;
	size_t m_size;
};


class MessageMultiPool 
{
public:
	ManagedMessagePtr acquire(size_t size)
	{
		return ManagedMessagePtr{ &pool, size };
	}

private:
	MessagePool pool;
};

