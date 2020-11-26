#pragma once

#include "IQueue.h"
#include "TQueue.h"
#include "IPoolResource.h"

#include <array>

namespace Pool::Resource
{
template <typename T>
class TBufferProxy : public IPoolResource<T>
{
public:
   template <size_t Size>
   TBufferProxy(std::array<T, Size>* buffer, TQueue<int, Size>* control) : m_pBuf(buffer->data()), m_pQ(control)
   {
      for( int i = 0; i < Size; i++ )
      {
         m_pQ->push(i);
      }
   };

   T* allocate();
   void free(T const* item);

private:
   T* m_pBuf;
   IQueue<T>* m_pQ;
};

template<typename T>
inline T* TBufferProxy<T>::allocate()
{
   if( m_pQ->count() == 0 )
   {
      return nullptr;
   }
   else
   {
      return &m_pBuf[m_pQ->pop()];
   }
}

template<typename T>
inline void TBufferProxy<T>::free(T const* item)
{
   m_pQ->push(std::distance<T const*>(m_pBuf, item));
}
}