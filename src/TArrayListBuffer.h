#pragma once
#include "TAlignedBuffer.h"
#include <array>

namespace pvt 
{
template <typename T, unsigned int Size>
class TArrayListBuffer
{
public:
	TAlignedBuffer<T, Size> memory;
	std::array<int, Size> queue;
	std::array<int, Size> map;
};
}