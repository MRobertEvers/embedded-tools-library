#pragma once
#include "IMessage.h"

#include "send_message.h"

namespace Actor
{
class IRouter
{
public:
	virtual ~IRouter(){}

	inline bool accepts(IMessage const* msg)
	{
		return handle_accepts(msg);
	}

protected:
	inline void post_message(IMessage const* const msg)
	{
		handle_post_message(msg);
	}

	virtual bool handle_accepts(IMessage const* const msg) const = 0;
	virtual void handle_post_message(IMessage const* const msg) = 0;

public:
	friend void send_message(IRouter* router, IMessage const* const msg);
};
}

