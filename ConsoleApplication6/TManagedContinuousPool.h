#pragma once
#include "TContinuousPool.h"
#include "ControlBlock.h"
#include "TManaged.h"

#include <array>

namespace Pool::Managed
{
template <typename T>
class TManagedContinuousPool
{
public:
   template <size_t Size>
   TManagedContinuousPool(
      std::array<T, Size>* buffer, 
      std::array<int, Size>* queue, 
      std::array<ControlBlock, Size>* control
   ) 
      : m_pool(buffer, queue), m_pControlBlocks(control->data())
   {
   };

   template <size_t Size>
   TManagedContinuousPool(
      Resource::TStaticPoolBuffer<T, Size>* resource,
      std::array<ControlBlock, Size>* control
   )
      : TManagedContinuousPool(resource->buffer, resource->control, control)
   {
   };

   TManaged<T> acquire()
   {
      if( m_pool.numAvailable() == 0 )
      {
         return TManaged<T>(nullptr);
      }
      else
      {
         auto cb = &m_pControlBlocks[m_nextControlBlock];
         
         m_nextControlBlock = (m_nextControlBlock + 1) % m_pool.size();

         return TManaged<T>{&m_pool, cb};
      }
   }

private:
   TContinuousPool<T> m_pool;
   ControlBlock* m_pControlBlocks;
   // We know the pool and the control blocks array are the same size, so we can just 
   // use control blocks round robbin.
   int m_nextControlBlock;
};
}

