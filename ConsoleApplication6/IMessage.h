#pragma once

namespace Actor
{
class IMessage
{
public:
	virtual int sendTo() = 0;
	virtual int replyTo() = 0;
	virtual int type() = 0;
	virtual int size() = 0;
	virtual void* data() = 0;
};
}

