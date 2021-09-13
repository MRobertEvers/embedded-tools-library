#pragma once
#include "IMessage.h"

namespace pvt
{
class IActorQueue
{
public:
	inline bool put_message(IMessage const* const msg) { return handle_put_message(msg); };

	inline IMessage const* get_message() { return handle_get_message(); };

private:
	virtual bool handle_put_message(IMessage const* const msg) = 0;
	virtual IMessage const* handle_get_message() = 0;
};
} // namespace pvt
