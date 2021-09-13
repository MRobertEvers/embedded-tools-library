#pragma once
#include "IMessage.h"
#include "TLockGuard.h"
#include <cstdint>


namespace pvt
{
struct timer
{
	bool auto_reload_;
	uint32_t sig_;
	uint32_t address_;

	uint32_t expiration_;
	uint32_t prime_;
	struct timer* p_next_;

	// Storage for the message.
	IMessage msg_;
};
typedef struct timer timer_t;

class ITimerDispatch
{
public:
	virtual void timer_fired(uint32_t address, IMessage const* msg) = 0;
};

template <typename Mutex>
class TimerModule
{
public:
	TimerModule(ITimerDispatch* dispatch)
		: dispatch_(dispatch){};
	void stop_timer(timer_t* timer);
	void start_timer(timer_t* timer, uint32_t address, uint32_t sig, uint32_t time_ms, bool auto_reload);
	void on_tick_isr(uint32_t current_tick);

private:
	ITimerDispatch* dispatch_;

	Mutex mutex_;
	timer_t* list_;
	uint32_t current_tick_;

	void prime_timer(timer_t* timer);
	void remove_timer(timer_t* timer);
	void append_timer(timer_t* timer);
};

template<typename Mutex>
inline void
TimerModule<Mutex>::stop_timer(timer_t* timer)
{
	TLockGuard<Mutex> lock(mutex_);

	remove_timer(timer);
}

template<typename Mutex>
inline void
TimerModule<Mutex>::start_timer(timer_t* timer, uint32_t module, uint32_t sig, uint32_t time_ms, bool auto_reload)
{
	TLockGuard<Mutex> lock(mutex_);

	timer->address_ = module;
	timer->sig_ = sig;
	timer->auto_reload_ = auto_reload;

	timer->p_next_ = nullptr;
	timer->prime_ = time_ms;

	prime_timer(timer);
	append_timer(timer);
}

template<typename Mutex>
inline void
TimerModule<Mutex>::on_tick_isr(uint32_t current_tick)
{
	current_tick_ = current_tick;

	timer_t* timer = list_;
	while( timer )
	{
		if( current_tick > timer->expiration_ )
		{
			timer->msg_.sig = timer->sig_;
			dispatch_->timer_fired(timer->address_, &timer->msg_);
		}

		timer = timer->p_next_;
	}

	timer = list_;
	while( timer )
	{
		if( current_tick > timer->expiration_ )
		{
			if( timer->auto_reload_ )
			{
				prime_timer(timer);
			}
			else
			{
				remove_timer(timer);
			}
		}

		timer = timer->p_next_;
	}
}

template<typename Mutex>
inline void
TimerModule<Mutex>::prime_timer(timer_t* timer)
{
	timer->expiration_ = current_tick_ + timer->prime_;
}

template<typename Mutex>
inline void
TimerModule<Mutex>::remove_timer(timer_t* timer)
{
	timer_t* prev_timer = list_;
	timer_t* curr_timer = list_;
	while( curr_timer )
	{
		if( curr_timer == timer )
		{
			if( curr_timer == list_ )
			{
				list_ = curr_timer->p_next_;
			}
			else
			{
				prev_timer->p_next_ = curr_timer->p_next_;
			}

			break;
		}

		prev_timer = curr_timer;
		curr_timer = curr_timer->p_next_;
	}
}

template<typename Mutex>
inline void
TimerModule<Mutex>::append_timer(timer_t* timer)
{
	timer_t* prev_timer = list_;
	timer_t* curr_timer = list_;
	while( curr_timer )
	{
		prev_timer = curr_timer;
		curr_timer = curr_timer->p_next_;
	}

	if( prev_timer == nullptr )
	{
		list_ = timer;
	}
	else
	{
		prev_timer->p_next_ = timer;
	}
}
} // namespace pvt
