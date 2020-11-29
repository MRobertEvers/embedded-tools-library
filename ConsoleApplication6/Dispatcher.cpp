#include "Dispatcher.h"

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

	auto end = std::stable_partition(
		m_actors.begin(), m_actors.end(),
		[&msg](auto actor) { return actor->subscribed(msg->type()); });

	for( auto iter = m_actors.begin(); iter != end; ++iter )
	{
		if( iter != end - 1 )
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
