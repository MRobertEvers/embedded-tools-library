#include "scratch.h"
#include "TArrayList.h"
#include "TManagedContiguousPool.h"
#include "TMessage.h"
#include "TStaticMultiPoolSource.h"
#include "TMultiPool.h"
#include "make_array.h"
#include "IMultiPoolSource.h"
#include "TManagedMultiPool.h"
#include "TStaticManagedMultiPoolSource.h"
#include "IManagedMultiPoolSource.h"
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

      std::cout << messageBuf[119].getPtr()->destAddr;
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

   {
      Pool::Managed::TStaticManagedMultiPoolSource<Actor::IMessage, Actor::TMessage<4>, 120, 4> p1;
      Pool::Managed::TStaticManagedMultiPoolSource<Actor::IMessage, Actor::TMessage<16>, 120, 16> p2;

      auto pools = make_array<Pool::IManagedMultiPoolSource<Actor::IMessage>*>(&p1, &p2);
      Pool::TManagedMultiPool<Actor::IMessage> mmpool(&pools);

      auto handle = mmpool.acquire(8);
      auto handle2 = mmpool.acquire(8);
   }
}