#pragma once

#include "TContiguousBuffer.h"
#include "TContiguousAllocator.h"
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
		TContiguousBuffer<T, Size>* memory, 
		std::array<int, Size>* stackBuf, 
		std::array<int, Size>* listBuf
	)
		: m_buf(reinterpret_cast<T*>(memory->buffer.data())), 
		available(stackBuf->data(), stackBuf->size()), 
		order(listBuf->data()), m_capacity(Size), m_size(0)
	{
		memset(order, 0x00, Size);
		for( int i = 0; i < Size; ++i )
		{
			available.push(i);
		}
	};

	template <size_t Size>
	TArrayList(
		TArrayListBuffer<T, Size>* buffer
	) : TArrayList(&buffer->memory, &buffer->queue, &buffer->map)
	{

	}

	template <typename ...Args>
	void emplace(Args&& ...args)
	{
		if( m_size < m_capacity )
		{
			auto newItem = available.pop();

			void* buffer = &m_buf[newItem];
			new (buffer) T(std::forward<Args>(args)...);
			order[m_size] = newItem;

			m_size += 1;
		}
	}

	T* at(int i)
	{
		if( i > m_size )
		{
			return nullptr;
		}

		return &m_buf[order[i]];
	}

	void pop(int i)
	{
		if( i >= m_size )
		{
			return;
		}

		auto removed = order[i];
		if( i < m_capacity - 1 )
		{
			memmove(order + i, order + i + 1, m_size - i - 1);
		}

		auto item = &m_buf[removed];
		item->T::~T();

		available.push(removed);

		m_size -= 1;
	}

	int size()
	{
		return m_size;
	}

	int capacity()
	{
		return m_capacity;
	}

private:
	T* m_buf;
	TQueue<int> available;
	int* order;
	int m_capacity;
	int m_size;
};

