#pragma once
#include "IActorQueue.h"

class BaseActor : public Actor::IRouter
{
public:
	BaseActor(IActorQueue* q) : q_(q)
	{

	}

	virtual bool subscribed(int msgType) = 0;

	void postMessage(MessageHandle msg)
	{
		q_->putMessage(msg);
	}

	void process()
	{
		auto msg = q_->getMessage();

		handleMessage(msg.operator->());
	}

protected:
	virtual void handleMessage(IMessage const* msg) = 0;

private:
	IActorQueue* q_;
};

