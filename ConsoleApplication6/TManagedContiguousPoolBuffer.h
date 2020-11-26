#pragma once
#include "ControlBlock.h"

namespace Pool::Resource
{
template <typename T, size_t Size>
class TManagedContiguousPoolBuffer
{
public:
   T buffer[Size];
   std::array<int, Size> queue;
   std::array<Managed::ControlBlock, Size> control;
};

}