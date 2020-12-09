#include "send_message.h"
#include "IRouter.h"
#include "IMessage.h"

void Actor::send_message(IRouter* router, IMessage const* const msg)
{
	if( router->accepts(msg) )
	{
		router->post_message(msg);
	}
}
