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

	int sendTo() override;
	int replyTo() override;
	int type() override;
	int size() override
	{
		return Size;
	};
	void* data() override;

	//template<typename T, typename... Args>
	//void construct(Args&&... args);
	//{
	//	static_assert(std::is_trivially_destructible<T>::value);
	//	static_assert(sizeof(T) <= Size);

	//	new (buffer) T(std::forward<Args>(args)...);
	//}

	short destAddr;
	short replyAddr;
	short messageType;
	char buffer[Size];


};

template<size_t Size>
inline void Actor::TMessage<Size>::build(int dest, int resp, int type, char* data, int size)
{
	destAddr = dest;
	replyAddr = resp;
	messageType = type;
	memcpy_s(buffer, sizeof(buffer), data, size);
}

template<size_t Size>
inline int TMessage<Size>::sendTo()
{
	return destAddr;
}

template<size_t Size>
inline int TMessage<Size>::replyTo()
{
	return replyAddr;
}

template<size_t Size>
inline int TMessage<Size>::type()
{
	return messageType;
}

template<size_t Size>
inline void* TMessage<Size>::data()
{
	return buffer;
}

}
