#pragma once
#include "IMultiPoolSource.h"
#include "IMultiPool.h"

#include <algorithm>
#include <array>

namespace Pool
{
template <typename T>
class TMultiPool : public IMultiPool<T>
{
public:
	template <size_t Size>
	TMultiPool(std::array<IMultiPoolSource<T>*, Size>* sources)
		: m_sources(sources->data()), m_sourcesLen(Size)
	{
		// Sort smallest first
		std::sort(
			sources->begin(),
			sources->end(),
			[](auto poolA, auto poolB) { 
			return poolA->objectSize() < poolB->objectSize(); 
		});
	};

	virtual T* acquire(size_t size) override
	{
		for( size_t i = 0; i < m_sourcesLen; ++i )
		{
			if( size < m_sources[i]->objectSize() )
			{
				return m_sources[i]->acquire();
			}
		}

		return nullptr;
	};

	virtual void release(T const* item, size_t size) override
	{
		for( size_t i = 0; i < m_sourcesLen; ++i )
		{
			if( size < m_sources[i]->objectSize() )
			{
				return m_sources[i]->release(item);
			}
		}
	};

private:
	IMultiPoolSource<T>** m_sources;
	size_t m_sourcesLen;
};
}

