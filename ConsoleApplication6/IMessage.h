#pragma once

namespace Actor
{
class IMessage
{
	// TODO: Probably don't need all of these.
public:
	virtual void build(int dest, int resp, int type, char* data, int size) = 0;

	virtual int sendTo() const = 0;
	virtual int replyTo() const = 0;
	virtual int type() const = 0;
	virtual int size() const = 0;
	virtual void const* data() const = 0;
};
}

