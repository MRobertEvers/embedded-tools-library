#pragma once
#include "IMessagePool.h"
#include "ActorModel.h"

#include <vector>

namespace Actor
{
class Dispatcher
{
public:
	Dispatcher(IMessagePool* pool)
		: m_pool(pool)
	{

	};

	void sendMessage(int dest, int resp, int type, char* data, int size);

	void registerActor(ActorModel* act)
	{
		m_actors.push_back(act);
	}

private:
	std::vector<Actor::ActorModel*> m_actors;
	IMessagePool* m_pool;
};
}

