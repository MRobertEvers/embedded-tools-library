#pragma once
#include "IMessage.h"
#include "IRouter.h"

namespace pvt
{
inline bool
send_message(IRouter* router, IMessage const* const msg)
{
	if( router->accepts(msg) )
	{
		return router->post_message(msg);
	}

	return false;
}
} // namespace pvt
