#pragma once
#include "IMessage.h"

namespace Actor
{
class IRouter
{
public:
	virtual bool accepts(IMessage const* msg) = 0; // TODO: Const?
	virtual void receive(IMessage const* msg) = 0;
};

inline void 
send_message(IRouter* router, IMessage const* msg)
{
	if( router->accepts(msg) )
	{
		router->receive(msg);
	}
}
}

