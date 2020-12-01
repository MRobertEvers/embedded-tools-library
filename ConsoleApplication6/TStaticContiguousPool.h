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
	// CAREFUL! These members are initialized AFTER the base class (which may modify this buffer)
	Resource::TContiguousPoolBuffer<T, Size> buffer;
};
}

