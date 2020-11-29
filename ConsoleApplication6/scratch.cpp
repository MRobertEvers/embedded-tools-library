#include "scratch.h"
#include "TArrayList.h"
#include "TManagedContiguousPool.h"
#include "TMessage.h"
#include "MessageMultiPool.h"
#include "TStaticMultiPoolSource.h"
#include "TMultiPool.h"
#include "make_array.h"
#include "IMultiPoolSource.h"

#include <iostream>
#include <array>

void scratch()
{
   std::array<int, 120u> messageQ;
   std::array<Pool::Managed::TManagedStorage<Actor::TMessage<32>>, 120u> messageBuf;
   Pool::Managed::TManagedContiguousPool<Actor::TMessage<32>> messagePool(&messageBuf, &messageQ);

   {
      auto msg = messagePool.acquire();
      msg->destAddr = 1;

      std::cout << messageBuf[119].object.destAddr;
   }

   TArrayListBuffer<std::string, 120> listBuf;
   TArrayList<std::string> list(&listBuf);

   list.emplace("wowow");

   std::cout << *list.at(0);

   Pool::TStaticMultiPoolSource<Actor::IMessage, Actor::TMessage<4>, 120, 4> smallpool;
   Pool::TStaticMultiPoolSource<Actor::IMessage, Actor::TMessage<16>, 120, 16> medpool;
   auto arr = make_array<Pool::IMultiPoolSource<Actor::IMessage>*>(&smallpool, &medpool);

   Pool::TMultiPool<Actor::IMessage> mpool(&arr);

   Actor::IMessage* p = mpool.acquire(8);

   mpool.release(p, 8);
}