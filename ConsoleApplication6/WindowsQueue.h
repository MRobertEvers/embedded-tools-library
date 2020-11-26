#pragma once
#include "IActorQueue.h"
#include "TStaticQueue.h"

#include <mutex>
#include <condition_variable>

class WindowsQueue : public Actor::IActorQueue
{
public:
	// Inherited via IActorQueue
	virtual void putMessage(Actor::IMessage* msg) override;
	virtual Actor::IMessage* getMessage() override;

private:
	std::condition_variable m_signal;
	std::mutex m_mutex;
	TStaticQueue<Actor::IMessage*, 10> m_q;
};

