#pragma once

namespace pvt
{
class IActor;
class AutomaticMessage;
using MessageSignalType = unsigned int;
class IMessage
{
public:
	MessageSignalType sig;

	virtual ~IMessage() {}

private:
	friend class AutomaticMessage;
	friend class IActor;
	virtual void acquire() const {};
	virtual void release() const {};
};
} // namespace pvt
