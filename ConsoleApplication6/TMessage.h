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
	int type() const override;
	size_t size() const override;
	void const* data() const override;

	void build(int type, void const* data, size_t size) override;
	//template<typename T, typename... Args>
	//void construct(Args&&... args);
	//{
	//	static_assert(std::is_trivially_destructible<T>::value);
	//	static_assert(sizeof(T) <= Size);

	//	new (buffer) T(std::forward<Args>(args)...);
	//}


	int type_ = 0;
	char buffer_[Size] = { 0 };
};

template<size_t Size>
inline size_t TMessage<Size>::size() const
{
	return Size;
}

template<size_t Size>
inline int TMessage<Size>::type() const
{
	return type_;
}

template<size_t Size>
inline void const* TMessage<Size>::data() const
{
	return buffer_;
}

template<size_t Size>
inline void Actor::TMessage<Size>::build(int type, void const* data, size_t size)
{
	type_ = type;
	memset(buffer_, 0x00, sizeof(buffer_));
	memcpy_s(buffer_, sizeof(buffer_), data, size);
}
}
