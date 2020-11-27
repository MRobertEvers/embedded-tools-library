#pragma once

#include <array>

namespace Pool::Resource
{
template <typename T, size_t Size>
class TContiguousPoolBuffer
{
public:
   std::array<T, Size> buffer;
   std::array<int, Size> control;
};

}