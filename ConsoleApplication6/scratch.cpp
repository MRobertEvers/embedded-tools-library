#include "scratch.h"
#include "TArrayList.h"
#include "TMessage.h"
#include "TStaticMultiPoolSource.h"
#include "TMultiPool.h"
#include "make_array.h"
#include "IMultiPoolSource.h"

#include <iostream>
#include <array>

void arraylist()
{
   TArrayListBuffer<std::string, 120> listBuf;
   TArrayList<std::string> list(&listBuf);

   list.emplace_back("wowow");

   std::cout << *list.at(0);

   for( auto arr : list )
   {
      std::cout << arr;
   }
}

void multipool()
{
   //Pool::TStaticMultiPoolSource<Actor::IMessage, Actor::TMessage<4>, 120, 4> smallpool;
   //Pool::TStaticMultiPoolSource<Actor::IMessage, Actor::TMessage<16>, 120, 16> medpool;
   //auto arr = make_array<Pool::IMultiPoolSource<Actor::IMessage>*>(&smallpool, &medpool);

   //Pool::TMultiPool<Actor::IMessage> mpool(&arr);

   //Actor::IMessage* p = mpool.acquire(8);

   //mpool.release(p, 8);
}

void scratch()
{
   arraylist();
   multipool();
}