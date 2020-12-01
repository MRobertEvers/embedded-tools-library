#pragma once
#include "IStack.h"

template <typename T>
class TStack : public IStack<T>
{
public:
   TStack(T* buffer, int size)
      : buf_(buffer), size_(size)
   {
   };

   virtual ~TStack(){ }

   bool push(const T& item) override;
   void pop() override;
   T peek() override;

   size_t capacity() override
   {
      return size_;
   }

   size_t count() override
   {
      return top_;
   }

private:
   T* buf_;
   int size_ = 0;
   int top_ = 0;
};


template<typename T>
bool TStack<T>::push(const T& item)
{
   if( top_ < size_ )
   {
      buf_[top_] = item;
      top_ += 1;

      return true;
   }

   return false;
}

template<typename T>
void TStack<T>::pop()
{
   if( top_ > 0 )
   {
      top_ -= 1;
   }

}

template<typename T>
T TStack<T>::peek()
{
   auto item = buf_[top_ - 1];

   return item;
}
