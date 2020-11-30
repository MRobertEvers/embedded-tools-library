#pragma once

#include "TStack.h"
#include "IPool.h"
#include "TContiguousPoolBuffer.h"

#include <array>

namespace Pool
{
template <typename T>
class TContiguousPool : public IPool<T>
{
public:
   template <size_t Size>
   TContiguousPool(std::array<T, Size>* buffer, std::array<int, Size>* control)
      : m_pBuf(buffer->data()), m_q(control->data(), Size)
   {
      for( int i = 0; i < Size; i++ )
      {
         m_q.push(i);
      }
   };

   template <size_t Size>
   TContiguousPool(Resource::TContiguousPoolBuffer<T, Size>* resource)
      : TContiguousPool(&resource->buffer, &resource->control)
   {
   };

   T* acquire() override;
   void release(T const* item) override;

   int size() override
   {
      return m_q.capacity();
   }

   int numAvailable() override
   {
      return m_q.count();
   }

   int getItemIndex(T const* item);

private:
   int acquireNextIndex();

   TStack<int> m_q;
   T* m_pBuf;
};

template<typename T>
inline T* TContiguousPool<T>::acquire()
{
   // TODO: Synchronized version lock here.
   auto next = acquireNextIndex();
   if( next == -1 )
   {
      return nullptr;
   }
   else
   {
      return &m_pBuf[next];
   }
}

template<typename T>
inline void TContiguousPool<T>::release(T const* item)
{
   // TODO: Synchronized version lock here.
   m_q.push(getItemIndex(item));
}

template<typename T>
inline int TContiguousPool<T>::getItemIndex(T const* item)
{
   return std::distance<T const*>(m_pBuf, item);
}

template<typename T>
inline int TContiguousPool<T>::acquireNextIndex()
{
   if( m_q.count() == 0 )
   {
      return -1;
   }
   else
   {
      auto item = m_q.peek();
      m_q.pop();
      return item;
   };
}
}