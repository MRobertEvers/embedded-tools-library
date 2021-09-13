#pragma once

namespace pvt 
{
template <typename T>
class IStack
{
public:
   virtual bool push(const T& item) = 0;
   virtual void pop() = 0;
   virtual T peek() = 0;

   virtual unsigned int capacity() = 0;
   virtual unsigned int count() = 0;
};
}