#pragma once
#include "IQueue.h"

#include <array>

template <typename T>
class TQueue : public IQueue<T>
{
public:
   TQueue(T* buffer, int size) 
      : buf_(buffer), size_(size)
   {
   };

   virtual ~TQueue(){ }

   bool push(const T& item) override;
   T pop() override;

   size_t capacity() override
   {
      return size_;
   }

   size_t count() override;
private:
   T* buf_;
   int size_ = 0;
   int m_head = 0;
   int m_tail = 0;
   bool m_isFull = false;
};

template<typename T>
bool TQueue<T>::push(const T& item)
{
   if( !m_isFull )
   {
      buf_[m_head] = item;
      m_head = (m_head + 1) % size_;
      m_isFull = m_head == m_tail;

      return true;
   }

   return false;
}

template<typename T>
T TQueue<T>::pop()
{
   auto item = buf_[m_tail];

   if( m_isFull || m_head != m_tail )
   {
      m_isFull = false;

      m_tail = (m_tail + 1) % size_;
   }

   return item;
}

template<typename T>
inline size_t TQueue<T>::count()
{
   if( m_head >= m_tail )
   {
      return m_isFull ? size_ : (m_head - m_tail);
   }
   else
   {
      return size_ - (m_tail - m_head);
   }
}
