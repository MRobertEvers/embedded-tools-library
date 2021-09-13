#pragma once
#include "IActor.h"
#include "IActorQueue.h"
#include "IMultiPool.h"
#include "IPool.h"
#include "IPoolMessage.h"
#include "IRouter.h"

namespace pvt
{
class MessagePool;
bool send_from_pool(MessagePool* pool, pvt::IActorQueue* queue, unsigned int type, void const* data, unsigned int size);
bool send_from_pool(MessagePool* pool, pvt::IRouter* router, unsigned int type, void const* data, unsigned int size);

class AutomaticMessage
{
public:
	AutomaticMessage(IMessage* msg)
		: msg_(msg)
	{
		if( msg )
		{
			msg->acquire();
		}
	}

	~AutomaticMessage()
	{
		if( msg_ )
		{
			msg_->release();
		}
	}
	IMessage* get() { return msg_; }
	bool ok() { return msg_ != nullptr; }

	inline bool send(pvt::IRouter* router) { return send_message(router, msg_); }
	inline bool send(pvt::IActorQueue* queue) { return pvt::IActor::post_to_queue(queue, msg_); }

private:
	IMessage* msg_;
};

class MessagePool
{
public:
	MessagePool(pvt::IPool<IPoolMessage>* pool) { pool_ = pool; }

	MessagePool(pvt::IMultiPool<IPoolMessage>* pool)
	{
		multipool_ = pool;
		is_multi_pool_ = true;
	}

private:
	union
	{
		pvt::IPool<IPoolMessage>* pool_;
		pvt::IMultiPool<IPoolMessage>* multipool_;
	};
	bool is_multi_pool_ = false;

	// Friend function to access the acquire function.
	friend bool
	send_from_pool(MessagePool* pool, pvt::IActorQueue* queue, unsigned int type, void const* data, unsigned int size);
	friend bool
	send_from_pool(MessagePool* pool, pvt::IRouter* router, unsigned int type, void const* data, unsigned int size);
	inline AutomaticMessage acquire(unsigned int type, void const* data, unsigned int size)
	{
		IPoolMessage* msg = nullptr;
		if( is_multi_pool_ )
		{
			msg = multipool_->acquire(size);
		}
		else
		{
			msg = pool_->acquire();
		}

		if( msg )
		{
			msg->prepare(this, type, data, size);
		}

		return AutomaticMessage(msg);
	}

	// Friend class to access the release function.
	friend IPoolMessage;
	inline void release(IPoolMessage const* msg)
	{
		if( is_multi_pool_ )
		{
			multipool_->release(msg, msg->size());
		}
		else
		{
			pool_->release(msg);
		}
	}
};
} // namespace pvt