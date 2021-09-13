#pragma once
#include "IActorQueue.h"
#include "IMessage.h"
#include "TLockGuard.h"
#include "TStaticArrayList.h"

template<typename Mutex, unsigned int Size>
class TSynchronizedActorQueue : public pvt::IActorQueue
{
protected:
	// Inherited via IActorQueue
	virtual bool handle_put_message(pvt::IMessage const* msg) override;
	virtual pvt::IMessage const* handle_get_message() override;

private:
	pvt::TStaticArrayList<pvt::IMessage const*, Size> q_;
	Mutex mutex_;
};

template<typename Mutex, unsigned int Size>
bool
TSynchronizedActorQueue<Mutex, Size>::handle_put_message(pvt::IMessage const* msg)
{
	pvt::TLockGuard<Mutex> lock(mutex_);
	if( q_.size() < Size )
	{
		q_.emplace_back(msg);
		return true;
	}
	else
	{
		return false;
	}
}

template<typename Mutex, unsigned int Size>
pvt::IMessage const*
TSynchronizedActorQueue<Mutex, Size>::handle_get_message()
{
	pvt::TLockGuard<Mutex> lock(mutex_);
	auto item = q_.front();
	if( !item )
	{
		return nullptr;
	}

	q_.pop(0);
	return *item;
}
