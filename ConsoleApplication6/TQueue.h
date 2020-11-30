#pragma once
#include "IQueue.h"

#include <array>

template <typename T>
class TQueue : public IQueue<T>
{
public:
   TQueue(T* buffer, int size) 
      : m_pBuf(buffer), m_size(size)
   {
   };

   virtual ~TQueue(){ }

   bool push(const T& item) override;
   T pop() override;

   size_t capacity() override
   {
      return m_size;
   }

   size_t count() override;
private:
   T* m_pBuf;
   int m_size = 0;
   int m_head = 0;
   int m_tail = 0;
   bool m_isFull = false;
};

template<typename T>
bool TQueue<T>::push(const T& item)
{
   if( !m_isFull )
   {
      m_pBuf[m_head] = item;
      m_head = (m_head + 1) % m_size;
      m_isFull = m_head == m_tail;

      return true;
   }

   return false;
}

template<typename T>
T TQueue<T>::pop()
{
   auto item = m_pBuf[m_tail];

   if( m_isFull || m_head != m_tail )
   {
      m_isFull = false;

      m_tail = (m_tail + 1) % m_size;
   }

   return item;
}

template<typename T>
inline size_t TQueue<T>::count()
{
   if( m_head >= m_tail )
   {
      return m_isFull ? m_size : (m_head - m_tail);
   }
   else
   {
      return m_size - (m_tail - m_head);
   }
}
