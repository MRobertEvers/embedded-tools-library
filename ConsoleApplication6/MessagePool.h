#pragma once
#include "TManagedMultiPool.h"
#include "IMessage.h"
#include "IMessagePool.h"
#include "MessagePtr.h"
#include "IManagedMultiPoolSource.h"
#include "TStaticManagedMultiPoolSource.h"
#include "TMessage.h"

namespace Actor
{
template <size_t MessageSize, size_t NumMessages>
using StaticMessagePoolSource = Pool::Managed::TStaticManagedMultiPoolSource<Actor::IMessage, Actor::TMessage<MessageSize>, NumMessages, MessageSize>;

using IMessagePoolSource = Pool::IManagedMultiPoolSource<Actor::IMessage>;

class MessagePool : public IMessagePool
{
public:
	template <size_t Size>
	MessagePool(std::array<IMessagePoolSource*, Size>* sources) : m_pool(sources)
	{

	};

	MessagePtr acquire(size_t size);

private:
	Pool::TManagedMultiPool<Actor::IMessage, MessagePtr> m_pool;
};
}

