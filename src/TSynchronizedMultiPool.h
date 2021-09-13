#pragma once
#include "IMultiPool.h"
#include "IMultiPoolSource.h"
#include "TLockGuard.h"

#include <algorithm>
#include <array>

namespace pvt
{
template<typename T, typename Mutex>
class TSynchronizedMultiPool : public IMultiPool<T>
{
public:
	template<unsigned int Size>
	TSynchronizedMultiPool(std::array<IMultiPoolSource<T>*, Size>* sources)
		: sources_(sources->data())
		, sources_len_(Size)
	{
		// Sort smallest first
		std::sort(sources->begin(), sources->end(), [](auto poolA, auto poolB) {
			return poolA->item_size() < poolB->item_size();
		});
	};

	virtual ~TSynchronizedMultiPool() {}

	virtual T* acquire(unsigned int size) override
	{
		TLockGuard<Mutex> lock(mutex_);

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
		TLockGuard<Mutex> lock(mutex_);

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
	Mutex mutex_;
};
} // namespace pvt
