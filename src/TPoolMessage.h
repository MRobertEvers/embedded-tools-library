#pragma once
#include "IMessage.h"
#include "IPoolMessage.h"
#include "MessagePool.h"

#include <cstring>

namespace pvt
{
template<unsigned int Size>
class TPoolMessage : public IPoolMessage
{
public:
	unsigned int size() const override;
	unsigned short data_size() const override { return data_size_; };
	void const* data() const override;

	void prepare(MessagePool* src, MessageSignalType type, void const* data, unsigned int size) override;

protected:
	alignas(Size) char buffer_[Size] = {0};
};

template<unsigned int Size>
inline unsigned int
TPoolMessage<Size>::size() const
{
	return Size;
}

template<unsigned int Size>
inline void const*
TPoolMessage<Size>::data() const
{
	return buffer_;
}

template<unsigned int Size>
inline void
TPoolMessage<Size>::prepare(MessagePool* src, MessageSignalType sig, void const* data, unsigned int size)
{
	this->sig = sig;
	this->src_ = src;
	this->data_size_ = size;
	memset(buffer_, 0x00, Size);
	memcpy(buffer_, data, size);
}
} // namespace pvt