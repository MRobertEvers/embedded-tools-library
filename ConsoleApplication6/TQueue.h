#pragma once

#include "IQueue.h"

template <typename T, size_t Size>
class TQueue : public IQueue<T>
{
public:
   bool push(const T& item) override;
   T pop() override;

   size_t capacity() override
   {
      return Size;
   }

   size_t count() override;
private:
   T m_pBuf[Size];
   int m_head = 0;
   int m_tail = 0;
   bool m_isFull = false;
};

template<typename T, size_t Size>
bool TQueue<T, Size>::push(const T& item)
{
   if( !m_isFull )
   {
      m_pBuf[m_head] = item;
      m_head = (m_head + 1) % Size;
      m_isFull = m_head == m_tail;

      return true;
   }

   return false;
}

template<typename T, size_t Size>
T TQueue<T, Size>::pop()
{
   auto item = m_pBuf[m_tail];

   if( m_isFull || m_head != m_tail )
   {
      m_isFull = false;

      m_tail = (m_tail + 1) % Size;
   }

   return item;
}

template<typename T, size_t Size>
inline size_t TQueue<T, Size>::count()
{
   if( m_head >= m_tail )
   {
      return m_isFull ? Size : (m_head - m_tail);
   }
   else
   {
      return Size - (m_tail - m_head);
   }
}
