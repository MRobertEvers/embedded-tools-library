#include "MessageMultiPool.h"

MultiPoolElementStorage*
MessagePool::acquire(size_t size)
{
	if( size < 4 )
	{
		auto poolIndex = smallptrs.size();

		auto msg = smallpool.acquire();
		smallptrs.emplace(msg);

		elemlist.emplace(msg.operator->(), 1, poolIndex);

		return elemlist.back();
	}
	else if( size < 16 )
	{
		auto poolIndex = mediumptrs.size();

		auto msg = mediumpool.acquire();
		mediumptrs.emplace(msg);

		elemlist.emplace(msg.operator->(), 1, poolIndex);

		return elemlist.back();
	}
	else if( size < 32 )
	{
		auto poolIndex = largeptrs.size();

		auto msg = largepool.acquire();
		largeptrs.emplace(msg);

		elemlist.emplace(msg.operator->(), 1, poolIndex);

		return elemlist.back();
	}
	else
	{
		return nullptr;
	}
}

void 
MessagePool::release(MultiPoolElementStorage const* elem)
{
	auto item = &elem->object;
	if( item->poolId == 0 )
	{
		smallptrs.pop(item->poolIndex);
	}
	else if( item->poolId == 1 )
	{
		mediumptrs.pop(item->poolIndex);
	}
	else if( item->poolId == 2 )
	{
		largeptrs.pop(item->poolIndex);
	}
	else
	{
		// Do nothing
	}
}

int 
MessagePool::size()
{
    return elemlist.size();
}

