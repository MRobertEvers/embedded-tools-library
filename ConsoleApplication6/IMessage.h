#pragma once

namespace Actor
{
class IMessage
{
	// TODO: Probably don't need all of these.
public:
	virtual void build(int dest, int resp, int type, char* data, int size) = 0;

	virtual int sendTo() = 0;
	virtual int replyTo() = 0;
	virtual int type() = 0;
	virtual int size() = 0;
	virtual void* data() = 0;
};
}

