#pragma once
#include "TContiguousPoolBuffer.h"
#include "TContiguousPool.h"

namespace pvt
{
// TODO: Naming - std::arrayContiguousPool?
template <typename Interface, unsigned int Size, typename T = Interface>
class TStaticContiguousPool : public TContiguousPool<Interface, T>
{
public:
	TStaticContiguousPool() 
		: TContiguousPool<Interface, T>(&buffer)
	{
	};

	virtual ~TStaticContiguousPool(){ }
private:
	// CAREFUL! These members are initialized AFTER the base class (which may modify this buffer)
	Resource::TContiguousPoolBuffer<T, Size> buffer;
};
}

