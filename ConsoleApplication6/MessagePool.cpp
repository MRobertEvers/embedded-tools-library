#include "MessagePool.h"

namespace Actor
{
IMessage* MessagePool::acquire(size_t size)
{
	return pool_.acquire(size);
}

void 
MessagePool::release(IMessage const* msg)
{
	pool_.release(msg, msg->size());
}
}
