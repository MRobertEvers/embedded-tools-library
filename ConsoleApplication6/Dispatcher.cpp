#include "Dispatcher.h"
#include "TArrayList.h"

#include <algorithm>
namespace Actor
{
void Dispatcher::sendMessage(int dest, int resp, int type, char* data, int size)
{
	// TODO:
	auto msg = m_pool->acquire(size);
	if( !msg.ok() )
	{
		return;
	}

	msg->build(dest, resp, type, data, size);

	auto receiveEnd = std::stable_partition(
		begin(m_actors), end(m_actors),
		[&msg](auto actor) { return actor->subscribed(msg->type()); });

	for( auto iter = begin(m_actors); iter != receiveEnd; ++iter )
	{
		if( iter != receiveEnd - 1 )
		{
			(*iter)->postMessage(msg.clone());
		}
		else
		{
			(*iter)->postMessage(msg);
		}
	}
}
}
