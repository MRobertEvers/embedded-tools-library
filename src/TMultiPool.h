#pragma once
#include "IMultiPool.h"
#include "IMultiPoolSource.h"

#include <algorithm>
#include <array>

namespace pvt
{
template<typename T>
class TMultiPool : public IMultiPool<T>
{
public:
	template<unsigned int Size>
	TMultiPool(std::array<IMultiPoolSource<T>*, Size>* sources)
		: sources_(sources->data())
		, sources_len_(Size)
	{
		// Sort smallest first
		std::sort(sources->begin(), sources->end(), [](auto pool_a, auto pool_b) {
			return pool_a->item_size() < pool_b->item_size();
		});
	};

	virtual ~TMultiPool() {}

	virtual T* acquire(unsigned int size) override
	{
		for( unsigned int i = 0; i < sources_len_; ++i )
		{
			if( size <= sources_[i]->item_size() )
			{
				return sources_[i]->acquire();
			}
		}

		return nullptr;
	};

	virtual void release(T const* item, unsigned int size) override
	{
		for( unsigned int i = 0; i < sources_len_; ++i )
		{
			if( size <= sources_[i]->item_size() )
			{
				return sources_[i]->release(item);
			}
		}
	};

private:
	IMultiPoolSource<T>** sources_;
	unsigned int sources_len_;
};
} // namespace pvt
