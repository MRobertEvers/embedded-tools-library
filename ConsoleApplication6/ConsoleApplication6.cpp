// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "TContiguousPool.h"
#include "TManagedContiguousPool.h"
#include "TStaticQueue.h"
#include "TMessage.h"
#include "IMessage.h"
#include "TieredMessagePool.h"

#include <iostream>
#include <array>

void tpool()
{
   TieredMessagePool pool;

   {
      auto item = pool.acquire();
   }
}

int main()
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

    tpool();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

