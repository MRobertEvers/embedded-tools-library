#pragma once
#include "TArrayList.h"
#include "TArrayListBuffer.h"

template <typename T, size_t Size>
class TStaticArrayList : public TArrayList<T>
{
public:
	TStaticArrayList() 
		: TArrayList<T>(&buffer_){ };

private:
	TArrayListBuffer<T, Size> buffer_;
};

