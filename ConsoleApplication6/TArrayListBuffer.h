#pragma once
#include "TContiguousBuffer.h"
#include <array>

template <typename T, size_t Size>
class TArrayListBuffer
{
public:
	TContiguousBuffer<T, Size> memory;
	std::array<int, Size> queue;
	std::array<int, Size> map;
};

