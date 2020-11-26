#pragma once

template <typename T>
class IQueue
{
public:
   virtual bool push(const T& item) = 0;
   virtual T pop() = 0;

   virtual size_t capacity() = 0;
   virtual size_t count() = 0;
};
