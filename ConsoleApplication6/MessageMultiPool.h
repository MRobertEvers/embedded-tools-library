#pragma once
#include "IManagedPool.h"
#include "TContiguousPool.h"
#include "TManagedContiguousPool.h"

#include "SourceMap.h"
#include "MessageHandle.h"
#include "SourceMapPool.h"

#include <vector>

namespace Pool::MultiPool
{
class MessageMultiPool : public Pool::Managed::IManagedPool<MessageHandle, MessageHandle>
{
public:
	MessageMultiPool()
		: smallPool(&smallPoolBuffer), messagePool(&messageBuffer, &smallPoolHandles)
	{
	};

	MessageHandle acquire()
	{
		auto handle = Pool::Managed::TManaged<SourceMap>{ &messagePool };

		if( !handle.ok() )
		{
			return MessageHandle{ nullptr, handle };
		}
		else
		{
			auto item = smallPool.acquire();

			handle->prepare(smallPoolHandles.size());
			smallPoolHandles.push_back(item);

			return MessageHandle{ item.operator->(), handle };
		}
	}

private:
	Pool::Resource::TManagedContiguousPoolBuffer<Actor::TMessage<4>, 120> smallPoolBuffer;
	Pool::Managed::TManagedContiguousPool<Actor::TMessage<4>> smallPool;
	std::vector<Pool::Managed::TManaged<Actor::TMessage<4>>> smallPoolHandles;

	std::array<Pool::Managed::ControlBlock, 120> ctrlBlocks;
	Pool::Resource::TContiguousPoolBuffer<Pool::Managed::TManagedStorage<SourceMap>, 120> messageBuffer;
	SourceMapPool messagePool;
};
}
