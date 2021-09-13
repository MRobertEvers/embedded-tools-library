#pragma once

#include <array>

namespace pvt 
{
template <typename T, unsigned int NumElements>
class TAlignedBuffer
{
public:
	alignas(T) std::array<std::array<char, sizeof(T)>, NumElements> buffer;
};

}