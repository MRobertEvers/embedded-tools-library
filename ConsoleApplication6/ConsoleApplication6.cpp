// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "scratch.h"

#include "Dispatcher.h"
#include "MessagePool.h"
#include "CLIActor.h"
#include "LogFileActor.h"
#include "WindowsQueue.h"
#include "make_array.h"
#include "TMessage.h"
#include "TStaticMultiPoolSource.h"

#include <thread>
#include <iostream>
#include <array>

// TODO: Technically, these pools need to be synchronized...
// TODO: Delete the destructor to force these to be static duration?
//static Actor::MessagePoolSource<4, 2> p1;
//static Actor::MessagePoolSource<16, 2> p2;
//static auto pools = make_array<Actor::IMessagePoolSource*>(&p1, &p2);
//
//static Actor::MessagePool p{ &pools };
//static Actor::Dispatcher dispatcher{ &p };
//
//// TODO: Use a persistent QUEUE, and put the message into the queue.
//// The interrupt actor can receive from that queue and put it into the system.
//// Like an interrupt - specialize system for Queues.
//void io_thread()
//{
//   while( true )
//   {
//      char buf[50] = { 0 };
//      std::cin.getline(buf, sizeof(buf));
//      std::cin.clear();
//      dispatcher.sendMessage(1, buf, strnlen(buf, sizeof(buf)));
//   }
//}
//
//void cli_thread()
//{
//   WindowsQueue msgQ{};
//   CLIActor a{ &msgQ, &dispatcher };
//   // TODO: Separate registry!
//   dispatcher.registerActor(&a);
//   while( true )
//   {
//      a.process();
//   }
//}
//
//void log_thread()
//{
//   WindowsQueue msgQ{};
//   LogFileActor a{ &msgQ };
//   dispatcher.registerActor(&a);
//   while( true )
//   {
//      a.process();
//   }
//}

int main()
{
    scratch();
    //std::thread t1(&io_thread);
    //std::thread t2(&cli_thread);
    //std::thread t3(&log_thread);

    t1.join();
}
