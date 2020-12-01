#pragma once
#include "IMessagePool.h"
#include "IMessage.h"
#include "IControlBlock.h"

namespace Actor
{
class MessageHandle
{
public:
	MessageHandle(IMessagePool* pool, IControlBlock* ctrl, size_t size);
	MessageHandle(const MessageHandle& cpy);
	~MessageHandle();

	IMessage* operator->();
	bool ok();

	MessageHandle clone(IControlBlock* ctrl);

private:
	IMessagePool* pool_;
	IMessage* item_;
	IControlBlock* ctrl_;
};
}

