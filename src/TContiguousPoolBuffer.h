#pragma once

#include <array>

namespace pvt::Resource
{
template <typename T, unsigned int Size>
class TContiguousPoolBuffer
{
public:
   std::array<T, Size> buffer;
   std::array<int, Size> control;
};

}