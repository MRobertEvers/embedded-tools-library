#include "MessageHandle.h"

using namespace Actor;

// ctrl should be NON NULL
MessageHandle::MessageHandle(IMessagePool* pool, IControlBlock* ctrl, size_t size)
	: pool_(pool), item_(pool->acquire(size)), ctrl_(ctrl)
{
	if( item_ )
	{
		ctrl_->incRef();
	}
}

MessageHandle::MessageHandle(const MessageHandle& cpy)
{
	item_ = cpy.item_;
	pool_ = cpy.pool_;
	ctrl_ = cpy.ctrl_;

	if( item_ )
	{
		ctrl_->incRef();
	}
}

MessageHandle::~MessageHandle()
{
	if( item_ && pool_ && ctrl_->count() > 0 )
	{
		auto count = ctrl_->decRef();
		if( count == 0 )
		{
			pool_->release(item_);
		}
	}
}

IMessage* 
MessageHandle::operator->()
{
	return item_;
}

bool 
MessageHandle::ok()
{
	return item_ != nullptr;
}

MessageHandle 
MessageHandle::clone(IControlBlock* ctrl)
{
	auto cloned = MessageHandle{ pool_, ctrl, item_->size() };
	
	cloned->build(item_->type(), item_->data(), item_->size());

	return cloned;
}
