#pragma once
#include "MessageHandle.h"
#include "IActorQueue.h"
namespace Actor
{
class ActorModel
{
public:
	ActorModel(IActorQueue* q) : m_pQ(q)
	{

	}

	void postMessage(MessageHandle msg)
	{
		m_pQ->putMessage(msg);
	}

	void process()
	{
		auto msg = m_pQ->getMessage();

		handleMessage(msg);
	}

protected:
	virtual void handleMessage(MessageHandle msg) = 0;

private:
	IActorQueue* m_pQ;
};
}

