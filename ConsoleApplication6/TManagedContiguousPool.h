#pragma once
#include "TContiguousPool.h"
#include "TManagedContiguousPoolBuffer.h"
#include "TManagedPtr.h"
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

   virtual ~TManagedContiguousPool(){ }

   TManagedPtr<T> acquire()
   {
      if( m_pool.numAvailable() == 0 )
      {
         return TManagedPtr<T>{ nullptr };
      }
      else
      {
         return TManagedPtr<T>{ &m_pool };
      }
   }

   int allocated()
   {
      return m_pool.size() - m_pool.numAvailable();
   }
private:
   TContiguousPool<TManagedStorage<T>> m_pool;
};
}

