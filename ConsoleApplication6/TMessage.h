#pragma once
#include <type_traits>

#include "IMessage.h"

#include <cstring>

namespace Actor
{
template <size_t Size>
class TMessage : public IMessage
{
public:

	// Inherited via IMessage
	void build(int dest, int resp, int type, char* data, int size) override;

	int sendTo() const override;
	int replyTo() const override;
	int type() const override;
	int size() const override
	{
		return Size;
	};
	void const* data() const override;

	//template<typename T, typename... Args>
	//void construct(Args&&... args);
	//{
	//	static_assert(std::is_trivially_destructible<T>::value);
	//	static_assert(sizeof(T) <= Size);

	//	new (buffer) T(std::forward<Args>(args)...);
	//}

	short destAddr = 0;
	short replyAddr = 0;
	short messageType = 0;
	char buffer[Size] = { 0 };
};

template<size_t Size>
inline void Actor::TMessage<Size>::build(int dest, int resp, int type, char* data, int size)
{
	destAddr = dest;
	replyAddr = resp;
	messageType = type;
	memset(buffer, 0x00, sizeof(buffer));
	memcpy_s(buffer, sizeof(buffer), data, size);
}

template<size_t Size>
inline int TMessage<Size>::sendTo() const
{
	return destAddr;
}

template<size_t Size>
inline int TMessage<Size>::replyTo() const
{
	return replyAddr;
}

template<size_t Size>
inline int TMessage<Size>::type() const
{
	return messageType;
}

template<size_t Size>
inline void const* TMessage<Size>::data() const
{
	return buffer;
}

}
