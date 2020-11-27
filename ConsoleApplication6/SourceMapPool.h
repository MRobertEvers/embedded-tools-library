#pragma once
#include "TManagedStorage.h"
#include "TContiguousPool.h"
#include "TManaged.h"
#include "SourceMap.h"

#include "TMessage.h"

#include <vector>
namespace Pool::MultiPool
{
class SourceMapPool : public Pool::TContiguousPool<Pool::Managed::TManagedStorage<SourceMap>>
{
public:
	SourceMapPool(
		Pool::Resource::TContiguousPoolBuffer<Pool::Managed::TManagedStorage<SourceMap>, 120>* messageBuffer,
		std::vector<Pool::Managed::TManaged<Actor::TMessage<4>>>* a
	)
		: Pool::TContiguousPool<Pool::Managed::TManagedStorage<SourceMap>>(messageBuffer),
		smallPoolHandles(a)
	{

	};

	void release(Pool::Managed::TManagedStorage<SourceMap> const* item) override
	{
		smallPoolHandles->erase(smallPoolHandles->begin() + item->object.getSource());
	}
public:
	std::vector<Pool::Managed::TManaged<Actor::TMessage<4>>>* smallPoolHandles;

};
}