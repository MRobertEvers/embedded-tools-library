#pragma once
#include "IMultiPool.h"
#include "IPoolMessage.h"
#include "TLockGuard.h"

#include <cstring>

namespace pvt
{
template<unsigned int Size, typename Mutex>
class TSynchronizedPoolMessage : public IPoolMessage
{
public:
	unsigned int size() const override;
	void const* data() const override;

	void prepare(MessagePool* src, unsigned int type, void const* data, unsigned int size) override;

protected:
	alignas(Size) char buffer_[Size] = {0};
	mutable Mutex mutex_;

	virtual void acquire() const override;

	virtual void release() const override;
};

template<unsigned int Size, typename Mutex>
inline unsigned int
TSynchronizedPoolMessage<Size, Mutex>::size() const
{
	return Size;
}

template<unsigned int Size, typename Mutex>
inline void const*
TSynchronizedPoolMessage<Size, Mutex>::data() const
{
	return buffer_;
}

template<unsigned int Size, typename Mutex>
inline void
TSynchronizedPoolMessage<Size, Mutex>::prepare(MessagePool* src, unsigned int type, void const* data, unsigned int size)
{
	this->sig = type;
	this->src_ = src;
	this->data_size_ = size;
	memset(buffer_, 0x00, Size);
	memcpy(buffer_, data, size);
}

template<unsigned int Size, typename Mutex>
inline void
TSynchronizedPoolMessage<Size, Mutex>::acquire() const
{
	TLockGuard<Mutex> lock(mutex_);
	IPoolMessage::acquire();
}

template<unsigned int Size, typename Mutex>
inline void
TSynchronizedPoolMessage<Size, Mutex>::release() const
{
	TLockGuard<Mutex> lock(mutex_);
	IPoolMessage::release();
}
} // namespace pvt