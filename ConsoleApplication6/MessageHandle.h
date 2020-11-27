#pragma once
#include "TManaged.h"

#include "IMessage.h"

#include "SourceMap.h"

namespace Pool::MultiPool
{
class MessageHandle
{
public:
	MessageHandle(Actor::IMessage* msg, Pool::Managed::TManaged<SourceMap> info)
		: message(msg), poolData(info)
	{

	};

	bool ok()
	{
		return poolData.ok() && message != nullptr;
	}

	Actor::IMessage* operator->()
	{
		return message;
	};

private:
	Actor::IMessage* message;
	Pool::Managed::TManaged<SourceMap> poolData;
};
}