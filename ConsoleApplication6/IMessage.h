#pragma once

#include "send_message.h"

namespace Actor
{
class IActor;

using MessageType = unsigned char;
class IMessage
{
public:
	IMessage(MessageType type) : type_(type){ }
	size_t type() const
	{
		return type_;
	}

	virtual ~IMessage(){ }
	virtual void acquire() const = 0;
	virtual void release() const = 0;

	friend class IActor;
private:
	MessageType type_;
};
}

