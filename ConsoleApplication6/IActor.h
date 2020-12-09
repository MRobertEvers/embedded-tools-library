#pragma once

#include "IRouter.h"
#include "IActorQueue.h"

namespace Actor
{
class IActor : public IRouter
{
public:
	IActor(IActorQueue* q) : q_(q) { }

	inline void process_one()
	{
		auto msg = q_->get_message();

		if( msg )
		{
			handle_process_one(msg);
			msg->release();
		}
	}

private:
	IActorQueue* q_;

	virtual void handle_post_message(IMessage const* const msg)
	{
		msg->acquire();
		q_->put_message(msg);
	}

protected:
	virtual void handle_process_one(IMessage const* const msg) = 0;
};
}