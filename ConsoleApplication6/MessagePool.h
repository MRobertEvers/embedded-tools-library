#pragma once
#include "IMessage.h"
#include "IMessagePool.h"
#include "TMessage.h"
#include "TMultiPool.h"
#include "TStaticMultiPoolSource.h"

namespace Actor
{
template <size_t MessageSize, size_t Count>
using MessagePoolSource = Pool::TStaticMultiPoolSource<Actor::IMessage, Actor::TMessage<MessageSize>, Count, MessageSize>;

using IMessagePoolSource = Pool::IMultiPoolSource<IMessage>;

class MessagePool : public IMessagePool
{
public:
	template <size_t Size>
	MessagePool(std::array<IMessagePoolSource*, Size>* sources) : pool_(sources) {};

	IMessage* acquire(size_t size);
	void release(IMessage const* msg);

private:
	Pool::TMultiPool<Actor::IMessage> pool_;
};
}

