// noch.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Dispatcher.h"
#include "MessagePool.h"
#include "TStaticMultiPoolSource.h"
#include "TSynchronizedMultiPool.h"
#include "TSynchronizedPoolMessage.h"
#include "TimerModule.h"
#include "make_array.h"
#include "send_from_pool.h"

#include <Windows.h>
#include <array>
#include <iostream>
#include <mutex>

using namespace pvt;

class DefaultTimerDispatch : public ITimerDispatch
{
public:
	DefaultTimerDispatch(IRouter* router)
		: router_(router)
	{
	}
	void timer_fired(uint32_t address, IMessage const* msg) override { send_message(router_, msg); };

private:
	pvt::IRouter* router_;
};

static TStaticMultiPoolSource<IPoolMessage, TSynchronizedPoolMessage<1, std::mutex>, 16, 1> s_p_flag;
static TStaticMultiPoolSource<IPoolMessage, TSynchronizedPoolMessage<64, std::mutex>, 10, 64> s_p_small;
static TStaticMultiPoolSource<IPoolMessage, TSynchronizedPoolMessage<128, std::mutex>, 10, 128> s_p_medium;
static auto s_data_pool_srcs = make_array<IMultiPoolSource<IPoolMessage>*>(&s_p_flag, &s_p_small, &s_p_medium);
static TSynchronizedMultiPool<IPoolMessage, std::mutex> s_msg_pool_src{&s_data_pool_srcs};

MessagePool g_msg_pool{&s_msg_pool_src};
Dispatcher<10> g_dispatcher{};

DefaultTimerDispatch g_default_timer_dispatch{&g_dispatcher};
TimerModule<std::mutex> g_timer{&g_default_timer_dispatch};

#include "windows/CLIActor.h"
#include "windows/LogFileActor.h"
#include "windows/WindowsMessageQueue.h"

#include <chrono>

// Like an interrupt
void
tim_thread()
{
	static unsigned int tick = 0;
	while( true )
	{
		g_timer.on_tick_isr(tick);
		std::chrono::milliseconds start =
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		std::chrono::milliseconds stop =
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		auto inc = stop.count() - start.count();
		// std::cout << inc << std::endl;

		tick += inc;
		g_timer.on_tick_isr(tick);
	}
}

void
io_thread()
{
	while( true )
	{
		char buf[50] = {0};
		std::cin.getline(buf, sizeof(buf));
		send_from_pool(&g_msg_pool, &g_dispatcher, 1, buf, sizeof(buf));
	}
}

void
cli_thread()
{
	WindowsMessageQueue msgQ{};
	CLIActor a{&msgQ, &g_dispatcher};

	pvt::timer t;
	g_timer.start_timer(&t, 0, 3, 5000, true);

	// TODO: Separate registry!
	g_dispatcher.subscribe(&a);
	while( true )
	{
		a.process_one();
	}
}

void
log_thread()
{
	WindowsMessageQueue msgQ{};
	LogFileActor a{&msgQ};
	g_dispatcher.subscribe(&a);
	while( true )
	{
		a.process_one();
	}
}

class TestMessageClass
{
public:
	constexpr static int sig = 5;
};

class SubscriptionRouter
{
public:
	// C++11 and above.
	template<typename MessageType>
	using Member = int (SubscriptionRouter::*)(MessageType);

	struct Sub
	{
		int id;
		Member<void*> handler;
	};
	static std::array<Sub, 10> subs;

	SubscriptionRouter() { subscribe(&SubscriptionRouter::on_test_message); }

	void handle(int m, void* message)
	{
		for( int i = 0; i < 10; i++ )
		{
			auto& sub = subs[i];
			if( sub.id == m )
			{
				(this->*sub.handler)(message);
				break;
			}
		}
	}

	template<typename MessageType>
	constexpr void subscribe(Member<MessageType*> handler)
	{
		subs[0].id = MessageType::sig;
		subs[0].handler = (Member<void*>)(handler);
	}

	int on_test_message(TestMessageClass* p) { std::cout << "Wow"; return 0; }
};
std::array<SubscriptionRouter::Sub, 10> SubscriptionRouter::subs;

int
main()
{
	// assert_has_no_duplicates<foo>();

	//    constexpr auto opts = checked_arr(
	//      Arg_Opt_Tuple{"world", 'h', true},
	//      Arg_Opt_Tuple{"world", 'g', true},
	//      Arg_Opt_Tuple{"goodbye", 'i', false},
	//      Arg_Opt_Tuple{"hello", 'r', false}
	//   );

	SubscriptionRouter t;
	TestMessageClass w;

	t.handle(w.sig, &w);

	std::thread tim(&tim_thread);
	std::thread t1(&io_thread);
	std::thread t2(&cli_thread);
	std::thread t3(&log_thread);

	t1.join();

	return 0;
}
