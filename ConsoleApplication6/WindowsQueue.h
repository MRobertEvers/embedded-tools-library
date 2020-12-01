#pragma once
#include "IActorQueue.h"
#include "TStaticQueue.h"
#include "MessageHandle.h"

#include <mutex>
#include <condition_variable>
#include <vector>

class WindowsQueue : public Actor::IActorQueue
{
public:
	// Inherited via IActorQueue
	virtual void putMessage(Actor::MessageHandle msg) override;
	virtual Actor::MessageHandle getMessage() override;

private:
	std::condition_variable m_signal;
	std::mutex m_mutex;

	std::vector<Actor::MessageHandle> q_;
};

