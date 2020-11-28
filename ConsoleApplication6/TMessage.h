#pragma once
#include <type_traits>

#include "IMessage.h"

namespace Actor
{
template <size_t Size>
class TMessage : public IMessage
{
public:
	TMessage() = default;

	int sendTo() override;
	int replyTo() override;
	int type() override;
	int size() override
	{
		return Size;
	};
	void* data() override;

	template<typename T, typename... Args>
	void construct(Args&&... args);
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

template<size_t Size>
template<typename T, typename ...Args>
inline void TMessage<Size>::construct(Args&& ...args)
{
}

}
