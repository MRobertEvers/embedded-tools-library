#pragma once
#include "TManagedStorage.h"
#include "TContiguousPool.h"
#include "TManaged.h"
#include "SourceMap.h"

#include "TMessage.h"

#include <vector>
namespace Pool::MultiPool
{
class SourceMapPool : public TContiguousPool<Managed::TManagedStorage<SourceMap>>
{
public:
	SourceMapPool(
		Resource::TContiguousPoolBuffer<Managed::TManagedStorage<SourceMap>, 120>* messageBuffer,
		// TODO: This should be a releaser - not depend on the allocator
		TArrayList<Pool::Managed::TManaged<Actor::TMessage<50>>>* alloc
	)
		: TContiguousPool<Managed::TManagedStorage<SourceMap>>(messageBuffer),
		smallPoolHandles(alloc)
	{

	};

	void release(Managed::TManagedStorage<SourceMap> const* item) override
	{
		// deallocator->release(item->object.getSource(), item->object.getId()); // etc
		smallPoolHandles->pop(item->object.getSource());
	}

public:
	TArrayList<Pool::Managed::TManaged<Actor::TMessage<50>>>* smallPoolHandles;
};
}