#include "MessagePool.h"

namespace Actor
{
MessagePtr MessagePool::acquire(size_t size)
{
	return m_pool.acquire(size);
}
}
