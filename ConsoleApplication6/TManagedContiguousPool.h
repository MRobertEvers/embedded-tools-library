#pragma once
#include "TContiguousPool.h"
#include "TManagedContiguousPoolBuffer.h"
#include "TManaged.h"
#include "IManagedPool.h"
#include "TManagedStorage.h"

#include <array>

namespace Pool::Managed
{
template <typename T>
class TManagedContiguousPool : public IManagedPool<T>
{
public:
   template <size_t Size>
   TManagedContiguousPool(
      std::array<TManagedStorage<T>, Size>* buffer,
      std::array<int, Size>* queue
      )
      : m_pool(buffer, queue)
   {
   };

   template <size_t Size>
   TManagedContiguousPool(
      Resource::TManagedContiguousPoolBuffer<T, Size>* resource
   )
      : TManagedContiguousPool(&resource->buffer, &resource->queue)
   {
   };

   TManaged<T> acquire()
   {
      if( m_pool.numAvailable() == 0 )
      {
         return TManaged<T>{ nullptr };
      }
      else
      {
         return TManaged<T>{ &m_pool };
      }
   }

private:
   TContiguousPool<TManagedStorage<T>> m_pool;
};
}

