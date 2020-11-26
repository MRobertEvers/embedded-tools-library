// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "TContinuousPool.h"
#include "TManagedContinuousPool.h"
#include "TStaticQueue.h"
#include "TMessage.h"
#include "IMessage.h"

#include <iostream>
#include <array>


int main()
{
   std::array<int, 120u> q;
   std::array<int, 120u> buf;
   Pool::TContinuousPool<int> pool(&buf, &q);

   auto myInt = pool.acquire();
   *myInt = 5;

    std::cout << "Hello World!\n";
    std::cout << buf[0] << "\n";

    std::array<int, 120u> messageQ;
    std::array<Pool::Managed::ControlBlock, 120u> controlBuf;
    std::array<Actor::TMessage<32>, 120u> messageBuf;
    Pool::Managed::TManagedContinuousPool<Actor::TMessage<32>> messagePool(&messageBuf, &messageQ, &controlBuf);

    {
       auto msg = messagePool.acquire();
       msg->destAddr = 1;

       std::cout << messageBuf[0].destAddr;
    }
    
    
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

