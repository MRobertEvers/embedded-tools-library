// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "TContiguousPool.h"
#include "TManagedContiguousPool.h"
#include "TStaticQueue.h"
#include "TMessage.h"
#include "IMessage.h"
#include "MessageMultiPool.h"
#include "Dispatcher.h"
#include "CLIActor.h"
#include "WindowsQueue.h"
#include "TArrayList.h"

#include <thread>
#include <iostream>
#include <array>
//
static Actor::MessagePool::MessageMultiPool p;
static Dispatcher dispatcher(&p);

void io_thread()
{
   while( true )
   {
      char c = std::cin.get();
      dispatcher.sendMessage(1, static_cast<char*>(&c), 1);
   }
}

void cli_thread()
{
   WindowsQueue msgQ{};
   CLIActor a{ &msgQ };
   dispatcher.registerActor(&a);
   while( true )
   {
      a.process();
   }
}

void tpool()
{
   Actor::MessagePool::MessageMultiPool pool;

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

    TContiguousBuffer<std::string, 12> memory;
    std::array<int, 12> stackBuf;
    std::array<int, 12> listBuf;
    TArrayList<std::string> list(&memory, &stackBuf, &listBuf);

    list.emplace("wowow");

    std::cout << *list.at(0);

    tpool();

    std::thread t1(&io_thread);
    std::thread t2(&cli_thread);

    t1.join();
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

