#pragma once
#include "IStack.h"

template <typename T>
class TStack : public IStack<T>
{
public:
   TStack(T* buffer, int size)
      : m_pBuf(buffer), m_size(size)
   {
   };

   bool push(const T& item) override;
   void pop() override;
   T peek() override;

   size_t capacity() override
   {
      return m_size;
   }

   size_t count() override
   {
      return m_top;
   }

private:
   T* m_pBuf;
   int m_size = 0;
   int m_top = 0;
};


template<typename T>
bool TStack<T>::push(const T& item)
{
   if( m_top < m_size )
   {
      m_pBuf[m_top] = item;
      m_top += 1;

      return true;
   }

   return false;
}

template<typename T>
void TStack<T>::pop()
{
   if( m_top > 0 )
   {
      m_top -= 1;
   }

}

template<typename T>
T TStack<T>::peek()
{
   auto item = m_pBuf[m_top - 1];

   return item;
}
