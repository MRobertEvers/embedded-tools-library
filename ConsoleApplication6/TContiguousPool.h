#pragma once

#include "TStack.h"
#include "IPool.h"
#include "TContiguousPoolBuffer.h"

#include <array>

namespace Pool
{
template <typename T>
class TContiguousPool : public IPool<T>
{
public:
   template <size_t Size>
   TContiguousPool(std::array<T, Size>* buffer, std::array<int, Size>* control)
      : buf_(buffer->data()), q_(control->data(), Size)
   {
      for( int i = 0; i < Size; i++ )
      {
         q_.push(i);
      }
   };

   template <size_t Size>
   TContiguousPool(Resource::TContiguousPoolBuffer<T, Size>* resource)
      : TContiguousPool(&resource->buffer, &resource->control)
   {
   };

   virtual ~TContiguousPool(){}

   T* acquire() override;
   void release(T const* item) override;

   int size() override
   {
      return q_.capacity();
   }

   int numAvailable() override
   {
      return q_.count();
   }

   int getItemIndex(T const* item);

private:
   int acquireNextIndex();

   TStack<int> q_;
   T* buf_;
};

template<typename T>
inline T* TContiguousPool<T>::acquire()
{
   // TODO: Synchronized version lock here.
   auto next = acquireNextIndex();
   if( next == -1 )
   {
      return nullptr;
   }
   else
   {
      return &buf_[next];
   }
}

template<typename T>
inline void TContiguousPool<T>::release(T const* item)
{
   // TODO: Synchronized version lock here.
   q_.push(getItemIndex(item));
}

template<typename T>
inline int TContiguousPool<T>::getItemIndex(T const* item)
{
   return std::distance<T const*>(buf_, item);
}

template<typename T>
inline int TContiguousPool<T>::acquireNextIndex()
{
   if( q_.count() == 0 )
   {
      return -1;
   }
   else
   {
      auto item = q_.peek();
      q_.pop();
      return item;
   };
}
}