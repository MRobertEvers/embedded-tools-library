#pragma once

#include "TAlignedBuffer.h"
#include "TQueue.h"
#include "TArrayListBuffer.h"

#include <array>
#include <utility>

template <typename T>
class TArrayList
{
public:
	template <size_t Size>
	TArrayList(
		TArrayListBuffer<T, Size>* buffer
	) : TArrayList(&buffer->memory, &buffer->queue, &buffer->map)
	{

	}

	template <typename ...Args>
	void emplace_back(Args&& ...args)
	{
		if( size_ < capacity() )
		{
			auto newItem = available.pop();

			void* buffer = &m_buf[newItem];
			new (buffer) T(std::forward<Args>(args)...);
			order[size_] = newItem;

			size_ += 1;
		}
	}

	T* at(int i)
	{
		if( i > size_ )
		{
			return nullptr;
		}

		return &m_buf[order[i]];
	}

	T* operator[](int i)
	{
		return at(i);
	}

	T* back()
	{
		if( size_ == 0 )
		{
			return nullptr;
		}
		return at(size_-1);
	}

	void pop(int i = -1)
	{
		if( i >= size_ )
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
			memmove(order + i, order + i + 1, size_ - i - 1);
		}

		auto item = &m_buf[removed];
		item->T::~T();

		available.push(removed);

		size_ -= 1;
	}

	int size()
	{
		return size_;
	}

	int capacity()
	{
		return available.capacity();
	}

private:
	template <size_t Size>
	TArrayList(
		TAlignedBuffer<T, Size>* memory,
		std::array<int, Size>* stackBuf, 
		std::array<int, Size>* listBuf
	)
		: m_buf(reinterpret_cast<T*>(memory->buffer.data())), 
		available(stackBuf->data(), stackBuf->size()), 
		order(listBuf->data()), size_(0)
	{
		memset(order, 0x00, Size);
		for( int i = 0; i < Size; ++i )
		{
			available.push(i);
		}
	};

	T* m_buf;
	TQueue<int> available;
	// Keep a list of pointers to T*s 
	int* order;
	int size_;
};

template <typename T>
T* begin(TArrayList<T>& list)
{
	return list.at(0);
}

template <typename T>
T* end(TArrayList<T>& list)
{
	return list.back() + 1;
}

