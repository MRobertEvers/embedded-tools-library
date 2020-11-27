#pragma once

#include "TManagedStorage.h"

namespace Pool::Resource
{
template <typename T, size_t Size>
class TManagedContiguousPoolBuffer
{
public:
   std::array<Pool::Managed::TManagedStorage<T>, Size> buffer;
   std::array<int, Size> queue;
};

}