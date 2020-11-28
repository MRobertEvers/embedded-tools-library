#pragma once
#include "IManagedPool.h"
#include "TContiguousPool.h"
#include "TManagedContiguousPool.h"
#include "TContiguousAllocator.h"
#include "TArrayList.h"

#include "SourceMap.h"
#include "MessageHandle.h"
#include "SourceMapPool.h"


namespace Actor::MessagePool
{
class MessageMultiPool : public Pool::Managed::IManagedPool<Actor::MessageHandle, Actor::MessageHandle>
{
public:
	MessageMultiPool()
		: smallPool(&smallPoolBuffer), m_SourceMapPool(&messageBuffer, &smallPoolHandles),
		smallPoolHandles(&smallPoolHandlesBuffer)
	{
	};

	MessageHandle acquire()
	{
		auto handle = Pool::Managed::TManaged<Pool::MultiPool::SourceMap>{ &m_SourceMapPool };

		if( !handle.ok() )
		{
			return MessageHandle{ nullptr, handle };
		}
		else
		{
			auto item = smallPool.acquire();

			handle->prepare(smallPoolHandles.size());
			
			smallPoolHandles.emplace(item);

			return MessageHandle{ item.operator->(), handle };
		}
	}

private:
	Pool::Resource::TManagedContiguousPoolBuffer<Actor::TMessage<4>, 120> smallPoolBuffer;
	Pool::Managed::TManagedContiguousPool<Actor::TMessage<4>> smallPool;

	TArrayListBuffer<Pool::Managed::TManaged<Actor::TMessage<4>>, 120> smallPoolHandlesBuffer;
	TArrayList<Pool::Managed::TManaged<Actor::TMessage<4>>> smallPoolHandles;

	std::array<Pool::Managed::ControlBlock, 120> ctrlBlocks;
	Pool::Resource::TContiguousPoolBuffer<Pool::Managed::TManagedStorage<Pool::MultiPool::SourceMap>, 120> messageBuffer;
	Pool::MultiPool::SourceMapPool m_SourceMapPool;
};
}
