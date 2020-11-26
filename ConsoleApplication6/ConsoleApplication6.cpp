// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "TPool.h"
#include "TQueue.h"
#include "TBufferProxy.h"
#include "TMessage.h"

#include <array>

void test_q()
{

   TQueue<int, 5> tmp;

   for( int i = 0; i < 5; i++ )
   {
      tmp.push(i);
   }

   std::cout << tmp.pop();
   tmp.push(9);
   std::cout << tmp.pop();

   std::cout << tmp.pop();
   std::cout << tmp.pop();
   std::cout << tmp.pop();
   std::cout << tmp.pop();
}


int main()
{
   TQueue<int, 120u> q;
   std::array<int, 120u> buf;
   Pool::Resource::TBufferProxy<int> resource(&buf, &q);
   Pool::TPool<int> pool(&resource);

   auto myInt = pool.get();
   *myInt.operator->() = 5;

    std::cout << "Hello World!\n";
    std::cout << buf[0];

    Actor::TMessage<4> msg;

    msg.construct<int>();

    TQueue<int, 120u> messageQ;
    std::array<Actor::TMessage<32>, 120u> messageBuf;
    Pool::Resource::TBufferProxy<Actor::TMessage<32>> messagePoolResource(&messageBuf, &messageQ);
    Pool::TPool<Actor::TMessage<32>> messagePool(&messagePoolResource);

    auto r = messagePool.get();
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

