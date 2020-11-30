#pragma once
#include "TContiguousPoolBuffer.h"
#include "TContiguousPool.h"

namespace Pool
{
// TODO: Naming - TArrayContiguousPool?
template <typename T, size_t Size>
class TStaticContiguousPool : public TContiguousPool<T>
{
public:
	TStaticContiguousPool() 
		: TContiguousPool<T>(&buffer)
	{
	};

	virtual ~TStaticContiguousPool(){ }
private:
	Resource::TContiguousPoolBuffer<T, Size> buffer;
};
}

