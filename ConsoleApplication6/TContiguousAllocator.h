#pragma once
#include "IAllocator.h"
#include "IRandomAccessPool.h"
#include "TContiguousBuffer.h"

#include <array>

template <typename T>
class TContiguousAllocator : public IAllocator<T>
{
public:
	template <size_t NumElements>
	TContiguousAllocator(TContiguousBuffer<T, NumElements>* pool)
		: m_pool(pool->buffer)
	{
	};

	T* at(int i)
	{
		return m_pool.at(i);
	}
	
	T* allocate();
	void free(T* arg);

	int size()
	{
		return m_pool->size();
	}

	int numAllocated()
	{
		return m_pool.size() - m_pool.numAvailable();
	}

private:
	Pool::IRandomAccessPool<std::array<char, sizeof(T)>> m_pool;
};

template<typename T>
inline T* TContiguousAllocator<T>::allocate()
{
	auto buffer = m_pool.acquire();

	//if( !buffer )
	//{
	//	return nullptr;
	//}

	//auto item = new (buffer->data()) T();

	return reinterpret_cast<T*>(buffer);
}

template<typename T>
inline void TContiguousAllocator<T>::free(T* arg)
{
	//arg->T::~T();

	m_pool->release(reinterpret_cast<std::array<char, sizeof(T)>*>(arg));
}

