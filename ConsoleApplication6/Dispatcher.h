#pragma once
#include "IManagedPool.h"
#include "MessageHandle.h"
#include "ActorModel.h"

#include <vector>

class Dispatcher
{
public:
	Dispatcher(Pool::Managed::IManagedPool<Actor::MessageHandle, Actor::MessageHandle>* pool)
		: m_pool(pool)
	{

	};

	void sendMessage(int dest, char* data, int size)
	{
		auto msg = m_pool->acquire();
		memcpy(msg->data(), data, size);

		for( auto actor : m_actors )
		{
			actor->postMessage(msg);
		}
	}

	void registerActor(Actor::ActorModel* act)
	{
		m_actors.push_back(act);
	}
private:
	std::vector<Actor::ActorModel*> m_actors;
	Pool::Managed::IManagedPool<Actor::MessageHandle, Actor::MessageHandle>* m_pool;
};

