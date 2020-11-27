#pragma once
#include "TManagedContiguousPool.h";
#include "TManaged.h"
#include "TMessage.h"
#include "TContiguousPool.h"
#include "IManagedPool.h"
#include "ControlBlock.h"
#include "TContiguousPoolBuffer.h"
#include "TManagedContiguousPoolBuffer.h"
#include <vector>


class MH
{
public:
	MH() : source(-1)
	{
	};

	MH(int source) : source(source)
	{

	};

	void prepare(int src)
	{
		source = src;
	};

	int getSource() const
	{
		return source;
	};
private:
	int source;
};


class Message
{
public:
	Message(Actor::IMessage* msg, Pool::Managed::TManaged<MH> info)
		: message(msg), poolData(info)
	{

	};

	bool ok()
	{
		return poolData.ok() && message != nullptr;
	}

	Actor::IMessage* operator->()
	{
		return message;
	};

private:
	Actor::IMessage* message;

	Pool::Managed::TManaged<MH> poolData;
};

class MessagePool : public Pool::TContiguousPool<Pool::Managed::TManagedStorage<MH>>
{
public:
	MessagePool(
		Pool::Resource::TContiguousPoolBuffer<Pool::Managed::TManagedStorage<MH>, 120>* messageBuffer,
		std::vector<Pool::Managed::TManaged<Actor::TMessage<4>>>* a)
		: smallPoolHandles(a), Pool::TContiguousPool<Pool::Managed::TManagedStorage<MH>>(messageBuffer)
	{

	};

	void release(Pool::Managed::TManagedStorage<MH> const* item) override
	{
		smallPoolHandles->erase(smallPoolHandles->begin() + item->object.getSource());
	}
public:
	std::vector<Pool::Managed::TManaged<Actor::TMessage<4>>>* smallPoolHandles;

};

class TieredMessagePool : public Pool::Managed::IManagedPool<Message, Message>
{
public:
	TieredMessagePool() 
		: smallPool(&smallPoolBuffer), messagePool(&messageBuffer, &smallPoolHandles)
	{
	};

	Message acquire()
	{
		auto handle = Pool::Managed::TManaged<MH>{ &messagePool };
		
		if( !handle.ok() )
		{
			return Message{nullptr, handle};
		}
		else
		{
			auto item = smallPool.acquire();

			handle->prepare(smallPoolHandles.size());
			smallPoolHandles.push_back(item);

			return Message{item.operator->(), handle};
		}
	}

private:
	Pool::Managed::ControlBlock* getNextControlBlock()
	{
		return &ctrlBlocks[messagePool.getNextAvailableIndex()];
	}

	Pool::Resource::TManagedContiguousPoolBuffer<Actor::TMessage<4>, 120> smallPoolBuffer;
	Pool::Managed::TManagedContiguousPool<Actor::TMessage<4>> smallPool;
	std::vector<Pool::Managed::TManaged<Actor::TMessage<4>>> smallPoolHandles;

	std::array<Pool::Managed::ControlBlock, 120> ctrlBlocks;
	Pool::Resource::TContiguousPoolBuffer<Pool::Managed::TManagedStorage<MH>, 120> messageBuffer;
	MessagePool messagePool;
};

