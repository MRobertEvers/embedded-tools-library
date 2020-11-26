#pragma once
#pragma once

#include "IQueue.h"
#include "TQueue.h"
#include "IPoolResource.h"

#include <array>

namespace Pool::Resource
{
template <typename T, size_t Size>
class TPoolBuffer : public IPoolResource<T>
{
public:
   TPoolBuffer()
   {
      for( int i = 0; i < Size; i++ )
      {
         m_pQ->push(i);
      }
   };

   T* allocate();
   void free(T const* item);

private:
   T m_pBuf[Size];
   TQueue<T, Size> m_pQ;
};

template<typename T, size_t Size>
inline T* TPoolBuffer<T, Size>::allocate()
{
   if( m_pQ->count() == m_pQ->capacity() )
   {
      return nullptr;
   }
   else
   {
      return &m_pBuf[m_pQ->pop()];
   }
}

template<typename T, size_t Size>
inline void TPoolBuffer<T, Size>::free(T const* item)
{
   m_pQ->push(std::distance<T const*>(m_pBuf, item));
}
}