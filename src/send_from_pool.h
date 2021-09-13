#pragma once
#include "IActorQueue.h"
#include "IPoolMessage.h"
#include "MessagePool.h"

namespace pvt
{
inline bool
send_from_pool(MessagePool* pool, pvt::IActorQueue* queue, unsigned int type, void const* data, unsigned int size)
{
	bool sent = false;
	auto msg = pool->acquire(type, data, size);

	if( msg.ok() )
	{
		sent = msg.send(queue);
	}

	return sent;
}

inline bool
send_from_pool(MessagePool* pool, pvt::IRouter* router, unsigned int type, void const* data, unsigned int size)
{
	bool sent = false;
	auto msg = pool->acquire(type, data, size);

	if( msg.ok() )
	{
		sent = msg.send(router);
	}

	return sent;
}
} // namespace pvt