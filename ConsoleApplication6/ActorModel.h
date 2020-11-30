#pragma once
#include "IActorQueue.h"

namespace Actor
{
class ActorModel
{
public:
	ActorModel(IActorQueue* q) : m_pQ(q)
	{

	}

	virtual bool subscribed(int msgType) = 0;

	void postMessage(Actor::MessagePtr msg)
	{
		m_pQ->putMessage(msg);
	}

	void process()
	{
		auto msg = m_pQ->getMessage();

		handleMessage(msg.operator->());
	}

protected:
	virtual void handleMessage(Actor::IMessage const* msg) = 0;

private:
	IActorQueue* m_pQ;
};
}

