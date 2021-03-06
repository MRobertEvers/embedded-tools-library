#include "scratch.h"
#include "TArrayList.h"
#include "TManagedContiguousPool.h"
#include "TMessage.h"
#include "MessageMultiPool.h"

#include <iostream>
#include <array>

void tpool()
{
   Actor::MessagePool::MessageMultiPool pool;

   {
      auto item = pool.acquire();
   }
}

void scratch()
{
   std::array<int, 120u> q = { 0 };
   std::array<int, 120u> buffer;
   Pool::TContiguousPool<int> smallPool(&buffer, &q);

   auto myInt = smallPool.acquire();
   *myInt = 5;

   std::cout << "Hello World!\n";
   std::cout << buffer[119] << "\n";

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

   tpool();
}