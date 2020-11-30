#pragma once
#include "IMessagePool.h"
#include "ActorModel.h"

#include "TArrayList.h"

namespace Actor
{
class Dispatcher
{
public:
	Dispatcher(IMessagePool* pool)
		: m_actors(&m_actorBuffer), m_pool(pool)
	{

	};

	void sendMessage(int dest, int resp, int type, char* data, int size);

	void registerActor(ActorModel* act)
	{
		m_actors.emplace(act);
	}

private:
	TArrayListBuffer<Actor::ActorModel*, 10> m_actorBuffer;
	TArrayList<Actor::ActorModel*> m_actors;
	IMessagePool* m_pool;
};
}

