#pragma once
#include "IActorQueue.h"
#include "TStaticQueue.h"
#include "IMessage.h"

#include <mutex>
#include <condition_variable>
#include <vector>

class WindowsQueue : public Actor::IActorQueue
{
public:
	// Inherited via IActorQueue
	virtual void handle_put_message(Actor::IMessage const* msg) override;
	virtual Actor::IMessage const* handle_get_message() override;

private:
	std::condition_variable signal_;
	std::mutex mutex_;

	std::vector<Actor::IMessage const*> q_;
};

