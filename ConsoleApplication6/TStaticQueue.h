#pragma once

#include "TQueue.h"

template <typename T, size_t Size>
class TStaticQueue : public TQueue<T>
{
public:
   TStaticQueue() : TQueue(m_pBuf, Size)
   {
   };

private:
   T m_pBuf[Size];
};