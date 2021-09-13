#pragma once
#include "IQueue.h"

#include <array>
namespace pvt
{
template<typename T>
class TQueue : public IQueue<T>
{
public:
	TQueue(T* buffer, int size)
		: buf_(buffer)
		, size_(size){};

	virtual ~TQueue() {}

	bool push(const T& item) override;
	T pop() override;

	inline unsigned int capacity() const override { return size_; }

	unsigned int count() const override;

private:
	T* buf_;
	int size_ = 0;
	int head_ = 0;
	int tail_ = 0;
	bool isFull_ = false;
};

template<typename T>
bool
TQueue<T>::push(const T& item)
{
	if( !isFull_ )
	{
		buf_[head_] = item;
		head_ = (head_ + 1) % size_;
		isFull_ = head_ == tail_;

		return true;
	}

	return false;
}

template<typename T>
T
TQueue<T>::pop()
{
	auto item = buf_[tail_];

	if( isFull_ || head_ != tail_ )
	{
		isFull_ = false;

		tail_ = (tail_ + 1) % size_;
	}

	return item;
}

template<typename T>
inline unsigned int
TQueue<T>::count() const
{
	if( head_ >= tail_ )
	{
		return isFull_ ? size_ : (head_ - tail_);
	}
	else
	{
		return size_ - (tail_ - head_);
	}
}
} // namespace pvt