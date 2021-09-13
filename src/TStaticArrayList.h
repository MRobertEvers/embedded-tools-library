#pragma once
#include "TArrayList.h"
#include "TArrayListBuffer.h"
namespace pvt 
{
template <typename T, unsigned int Size>
class TStaticArrayList : public TArrayList<T>
{
public:
	TStaticArrayList() 
		: TArrayList<T>(&buffer_){ };

private:
	TArrayListBuffer<T, Size> buffer_;
};

}