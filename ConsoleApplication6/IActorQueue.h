#pragma once
#include "IMessage.h"

namespace Actor
{
class IActorQueue
{
public:
	void put_message(IMessage const* const msg)
	{
		handle_put_message(msg);
	};

	IMessage const* get_message()
	{
		return handle_get_message();
	};

private:
	virtual void handle_put_message(IMessage const* const msg) = 0;
	virtual IMessage const* handle_get_message() = 0;
};
}


