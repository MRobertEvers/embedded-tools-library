#pragma once

#include <array>

namespace Pool::Resource
{
template <typename T, size_t Size>
class TStaticPoolBuffer
{
public:
   T buffer[Size];
   std::array<int, Size> control;
};

}