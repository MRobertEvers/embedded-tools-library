#pragma once

#include "IQueue.h"
#include "TQueue.h"
#include "IPool.h"
#include "TStaticPoolBuffer.h"

#include <array>

namespace Pool
{
template <typename T>
class TPool : public IPool<T>
{
public:
   template <size_t Size>
   TPool(std::array<T, Size>* buffer, std::array<int, Size>* control) 
      : m_pBuf(buffer->data()), m_q(control->data(), Size)
   {
      for( int i = 0; i < Size; i++ )
      {
         m_q.push(i);
      }
   };

   template <size_t Size>
   TPool(Resource::TStaticPoolBuffer<T, Size>* resource)
      : TPool(resource->buffer, resource->control)
   {
   };

   T* acquire() override;
   void release(T const* item) override;

protected:
   int getItemIndex(T const* item);

private:
   TQueue<int> m_q;
   T* m_pBuf;
};

template<typename T>
inline T* TPool<T>::acquire()
{
   if( m_q.count() == 0 )
   {
      return nullptr;
   }
   else
   {
      return &m_pBuf[m_q.pop()];
   }
}

template<typename T>
inline void TPool<T>::release(T const* item)
{
   m_q.push(getItemIndex(item));
}

template<typename T>
inline int TPool<T>::getItemIndex(T const* item)
{
   return std::distance<T const*>(m_pBuf, item);
}
}