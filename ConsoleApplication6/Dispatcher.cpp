#include "Dispatcher.h"

#include <cstring>

void Dispatcher::sendMessage(int dest, int resp, int type, char* data, int size)
{
	// TODO:
	auto msg = m_pool->acquire();
	msg->build(dest, resp, type, data, size);

	for( auto actor : m_actors )
	{
		if( actor->subscribed(msg->type()) )
		{
			actor->postMessage(msg);
		}
	}
}
