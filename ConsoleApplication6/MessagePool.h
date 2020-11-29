#pragma once
#include "TManagedMultiPool.h"
#include "IMessage.h"
#include "IMessagePool.h"
#include "MessagePtr.h"
#include "IManagedMultiPoolSource.h"

namespace Actor
{
class MessagePool : public IMessagePool
{
public:
	template <size_t Size>
	MessagePool(std::array<Pool::IManagedMultiPoolSource<IMessage>*, Size>* sources) : m_pool(sources)
	{

	};

	MessagePtr acquire(size_t size);

private:
	Pool::TManagedMultiPool<Actor::IMessage> m_pool;
};
}

