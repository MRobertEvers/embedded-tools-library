#include "Dispatcher.h"
#include "TArrayList.h"
#include "MessageHandle.h"

#include <algorithm>

namespace Actor
{
void Dispatcher::sendMessage(int type, void const* data, size_t size)
{
	// TODO: Control blocks management
	ctrls_.emplace_back();
	auto msg = MessageHandle{ pool_, ctrls_.back(), size };
	if( !msg.ok() )
	{
		return;
	}

	msg->build(type, data, size);

	auto receiveEnd = std::stable_partition(
		begin(actors_), end(actors_),
		[&msg](auto actor) { return actor->subscribed(msg->type()); });

	for( auto iter = begin(actors_); iter != receiveEnd; ++iter )
	{
		if( iter != receiveEnd - 1 )
		{
			ctrls_.emplace_back();
			(*iter)->postMessage(msg.clone(ctrls_.back()));
		}
		else
		{
			(*iter)->postMessage(msg);
		}
	}
}
}
