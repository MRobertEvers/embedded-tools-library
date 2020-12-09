#pragma once
#include <type_traits>

#include "IMessage.h"

#include <cstring>

class IDataMessage : public Actor::IMessage
{
public:
	IDataMessage(Actor::MessageType type) : Actor::IMessage(type) { }

	virtual size_t size() const = 0;
	virtual void const* data() const = 0;
};

template <size_t Size>
class TMessage : public IDataMessage
{
public:
	TMessage(Actor::MessageType type) : IDataMessage(type), refCnt_(0), srcId_(0) { }

	char buffer_[Size] = { 0 };

	virtual size_t size() const override;
	virtual void const* data() const override;

	void build(void const* data, size_t dataSize);

protected:
	virtual void acquire() const override;
	virtual void release() const override;

	unsigned char srcId_;
	mutable unsigned char refCnt_;

public:
	static TMessage<Size> make_message(void const* data, size_t dataSize);
};

template<size_t Size>
inline void TMessage<Size>::acquire() const
{
	refCnt_++;
}

template<size_t Size>
inline void TMessage<Size>::release() const
{
	if( refCnt_ > 0 )
	{
		refCnt_--;
		if( refCnt_ == 0 )
		{
			// TODO:
		}
	}
}

template<size_t Size>
inline size_t TMessage<Size>::size() const
{
	return Size;
}

template<size_t Size>
inline void const* TMessage<Size>::data() const
{
	return buffer_;
}

template<size_t Size>
inline void TMessage<Size>::build(void const* data, size_t dataSize)
{
	*this = make_message(data, dataSize);
}

template<size_t Size>
inline TMessage<Size> TMessage<Size>::make_message(void const* data, size_t size)
{
	TMessage<Size> msg{ 2 };

	memset(msg.buffer_, 0x00, sizeof(msg.buffer_));
	memcpy_s(msg.buffer_, sizeof(msg.buffer_), data, size);

	return msg;
}
