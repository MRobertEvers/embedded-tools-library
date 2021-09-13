#pragma once

#include "TAlignedBuffer.h"
#include "TArrayListBuffer.h"
#include "TQueue.h"

#include <array>
#include <utility>

namespace pvt
{
template<typename T>
class TArrayList
{
public:
	template<unsigned int Size>
	TArrayList(TArrayListBuffer<T, Size>* buffer)
		: TArrayList(&buffer->memory, &buffer->queue, &buffer->map)
	{
	}

	template<typename... Args>
	inline void emplace_back(Args&&... args)
	{
		if( size_ < capacity() )
		{
			auto newItem = available.pop();

			void* buffer = &buf_[newItem];
			new(buffer) T(std::forward<Args>(args)...);
			order[size_] = newItem;

			size_ += 1;
		}
	}

	inline T* at(int i)
	{
		if( size_ == 0 || i > size_ )
		{
			return nullptr;
		}

		return &buf_[order[i]];
	}

	inline T const* c_at(int i) const
	{
		if( size_ == 0 || i > size_ )
		{
			return nullptr;
		}

		return &buf_[order[i]];
	}

	inline T* operator[](int i) { return at(i); }

	inline T* front() { return at(0); }

	inline T* back() { return at(size_ - 1); }

	inline void pop(int i = -1)
	{
		if( i >= size_ || size_ == 0 )
		{
			return;
		}
		else if( i == -1 )
		{
			i = size_ - 1;
		}

		auto removed = order[i];
		if( i < capacity() - 1 )
		{
			memmove(order + i, order + i + 1, sizeof(order[0]) * (size_ - i - 1));
		}

		auto item = &buf_[removed];
		item->T::~T();

		available.push(removed);

		size_ -= 1;
	}

	inline int size() const { return size_; }

	inline int capacity() const { return available.capacity(); }

private:
	template<unsigned int Size>
	TArrayList(TAlignedBuffer<T, Size>* memory, std::array<int, Size>* stackBuf, std::array<int, Size>* listBuf)
		: buf_(reinterpret_cast<T*>(memory->buffer.data()))
		, available(stackBuf->data(), stackBuf->size())
		, order(listBuf->data())
		, size_(0)
	{
		memset(order, 0x00, Size);
		for( int i = 0; i < Size; ++i )
		{
			available.push(i);
		}
	};

	T* buf_;
	TQueue<int> available;
	// Keep a list of pointers to T*s
	int* order;
	int size_;
};

template<typename T>
T*
begin(TArrayList<T>& list)
{
	return list.at(0);
}

template<typename T>
T*
end(TArrayList<T>& list)
{
	return list.back() + 1;
}

} // namespace pvt
