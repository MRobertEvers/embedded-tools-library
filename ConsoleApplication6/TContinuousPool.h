#pragma once

#include "IQueue.h"
#include "TQueue.h"
#include "IPool.h"
#include "TStaticPoolBuffer.h"

#include <array>

namespace Pool
{
template <typename T>
class TContinuousPool : public IPool<T>
{
public:
   template <size_t Size>
   TContinuousPool(std::array<T, Size>* buffer, std::array<int, Size>* control)
      : m_pBuf(buffer->data()), m_q(control->data(), Size)
   {
      for( int i = 0; i < Size; i++ )
      {
         m_q.push(i);
      }
   };

   template <size_t Size>
   TContinuousPool(Resource::TStaticPoolBuffer<T, Size>* resource)
      : TContinuousPool(resource->buffer, resource->control)
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

protected:
   int getNextAvailable();
   int getItemIndex(T const* item);

private:
   TQueue<int> m_q;
   T* m_pBuf;
};

template<typename T>
inline T* TContinuousPool<T>::acquire()
{
   auto next = getNextAvailable();
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
inline void TContinuousPool<T>::release(T const* item)
{
   m_q.push(getItemIndex(item));
}

template<typename T>
inline int TContinuousPool<T>::getNextAvailable()
{
   if( m_q.count() == 0 )
   {
      return -1;
   }
   else
   {
      return m_q.pop();
   };
}

template<typename T>
inline int TContinuousPool<T>::getItemIndex(T const* item)
{
   return std::distance<T const*>(m_pBuf, item);
}
}