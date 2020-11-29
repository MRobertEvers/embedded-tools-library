#pragma once

#include <array>

template <typename T, size_t NumElements>
class TAlignedBuffer
{
public:
	alignas(T) std::array<std::array<char, sizeof(T)>, NumElements> buffer;
};

