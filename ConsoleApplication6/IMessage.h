#pragma once

namespace Actor
{
class IMessage
{
public:
	virtual size_t type() const = 0;
};
}

