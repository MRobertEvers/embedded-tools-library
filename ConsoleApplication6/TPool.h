#pragma once

#include "IQueue.h"
#include "TQueue.h"
#include "IPoolResource.h"
#include "TPoolObjectHandle.h"

#include <array>

namespace Pool
{
template <typename T>
class TPool
{
public:
   TPool(IPoolResource<T>* resource) : m_pResource(resource)
   {
   };

   TPoolObjectHandle<T> get()
   {
      return TPoolObjectHandle(m_pResource);
   }

private:
   IPoolResource<T>* m_pResource;
};
}
