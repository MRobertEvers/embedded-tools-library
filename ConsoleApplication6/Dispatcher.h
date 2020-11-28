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

	void sendMessage(int dest, int resp, int type, char* data, int size);

	void registerActor(Actor::ActorModel* act)
	{
		m_actors.push_back(act);
	}

private:
	std::vector<Actor::ActorModel*> m_actors;
	Pool::Managed::IManagedPool<Actor::MessageHandle, Actor::MessageHandle>* m_pool;
};

