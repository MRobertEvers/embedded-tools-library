#pragma once
#include "TManagedMultiPoolPtr.h"
#include "IMessage.h"

namespace Actor
{
class MessagePtr
{
public:
	MessagePtr(Pool::Managed::TManagedMultiPoolPtr<IMessage> ptr)
		: msg(ptr)
	{

	};

	IMessage* operator->()
	{
		return msg.operator->();
	}

	bool ok()
	{
		return msg.ok();
	}

	MessagePtr clone()
	{
		return msg.clone();
	}

private:
	Pool::Managed::TManagedMultiPoolPtr<IMessage> msg;
};
}

