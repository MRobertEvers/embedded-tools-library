#pragma once
#include "IMessage.h"

namespace pvt
{
class IRouter;
bool send_message(IRouter* router, IMessage const* const msg);

class IRouter
{
public:
	virtual ~IRouter() {}

	inline bool accepts(IMessage const* msg) { return handle_accepts(msg); }

protected:
	friend bool send_message(IRouter* router, IMessage const* const msg);
	inline bool post_message(IMessage const* const msg) { return handle_post_message(msg); }

protected:
	virtual bool handle_accepts(IMessage const* const msg) const = 0;
	virtual bool handle_post_message(IMessage const* const msg) = 0;
};
} // namespace pvt
