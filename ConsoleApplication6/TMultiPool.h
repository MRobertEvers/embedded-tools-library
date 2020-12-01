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
		: sources_(sources->data()), sourcesLen_(Size)
	{
		// Sort smallest first
		std::sort(
			sources->begin(),
			sources->end(),
			[](auto poolA, auto poolB) { 
			return poolA->objectSize() < poolB->objectSize(); 
		});
	};

	virtual ~TMultiPool(){ }

	virtual T* acquire(size_t size) override
	{
		for( size_t i = 0; i < sourcesLen_; ++i )
		{
			if( size <= sources_[i]->objectSize() )
			{
				return sources_[i]->acquire();
			}
		}

		return nullptr;
	};

	virtual void release(T const* item, size_t size) override
	{
		for( size_t i = 0; i < sourcesLen_; ++i )
		{
			if( size <= sources_[i]->objectSize() )
			{
				return sources_[i]->release(item);
			}
		}
	};

private:
	IMultiPoolSource<T>** sources_;
	size_t sourcesLen_;
};
}

