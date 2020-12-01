#pragma once

namespace Actor
{
class IMessage
{
	// TODO: Probably don't need all of these.
public:
	virtual int type() const = 0;
	virtual size_t size() const = 0;
	virtual void const* data() const = 0;

	virtual void build(int type, void const* data, size_t size) = 0;
};
}

