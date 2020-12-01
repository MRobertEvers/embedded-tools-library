#pragma once

#include "TQueue.h"

template <typename T, size_t Size>
class TStaticQueue : public TQueue<T>
{
public:
   TStaticQueue() : TQueue(buf_, Size)
   {
   };

   virtual ~TStaticQueue(){ }

private:
   T buf_[Size];
};