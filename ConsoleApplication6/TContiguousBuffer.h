#pragma once

#include <array>

template <typename T, size_t NumElements>
class TContiguousBuffer
{
public:
	// TODO: Do I need this alignas?
	alignas(T) std::array<std::array<char, sizeof(T)>, NumElements> buffer;
};

