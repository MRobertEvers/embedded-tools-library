#pragma once

template <typename T>
class IStack
{
public:
   virtual bool push(const T& item) = 0;
   virtual void pop() = 0;
   virtual T peek() = 0;

   virtual size_t capacity() = 0;
   virtual size_t count() = 0;
};

