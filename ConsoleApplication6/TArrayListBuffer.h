#pragma once
#include "TAlignedBuffer.h"
#include <array>

template <typename T, size_t Size>
class TArrayListBuffer
{
public:
	TAlignedBuffer<T, Size> memory;
	std::array<int, Size> queue;
	std::array<int, Size> map;
};

