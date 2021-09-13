#pragma once

#include "IActorQueue.h"
#include "IRouter.h"

namespace pvt
{
class IActor : public IRouter
{
public:
	IActor(IActorQueue* q)
		: q_(q)
	{
	}

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

	virtual bool handle_post_message(IMessage const* const msg) { return post_to_queue(q_, msg); }

protected:
	virtual void handle_process_one(IMessage const* const msg) = 0;

public:
	static inline bool post_to_queue(IActorQueue* q, IMessage const* const msg)
	{
		msg->acquire();

		bool success = q->put_message(msg);
		if( !success )
		{
			msg->release();
		}

		return success;
	}
};
} // namespace pvt