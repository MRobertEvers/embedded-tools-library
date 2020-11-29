// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "scratch.h"

#include "Dispatcher.h"
#include "MessageMultiPool.h"
#include "CLIActor.h"
#include "LogFileActor.h"
#include "WindowsQueue.h"

#include <thread>
#include <iostream>
#include <array>
//
static MessageMultiPool p;
static Dispatcher dispatcher(&p);

// Like an interrupt
void io_thread()
{
   while( true )
   {
      char buf[50] = { 0 };
      std::cin.getline(buf, sizeof(buf));
      dispatcher.sendMessage(1, 0, 1, buf, strlen(buf));
   }
}

void cli_thread()
{
   WindowsQueue msgQ{};
   CLIActor a{ &msgQ, &dispatcher };
   // TODO: Separate registry!
   dispatcher.registerActor(&a);
   while( true )
   {
      a.process();
   }
}

void log_thread()
{
   WindowsQueue msgQ{};
   LogFileActor a{ &msgQ };
   dispatcher.registerActor(&a);
   while( true )
   {
      a.process();
   }
}

int main()
{
    std::thread t1(&io_thread);
    std::thread t2(&cli_thread);
    std::thread t3(&log_thread);

    t1.join();
}
