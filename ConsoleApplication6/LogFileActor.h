#pragma once
#include "BaseActor.h"
#include "IRouter.h"

class LogFileActor : public BaseActor
{
public:
	LogFileActor(Actor::IActorQueue* q) : Actor::ActorModel(q)
	{

	}

	// Inherited via ActorModel
	virtual bool subscribed(int msgType) override;
	virtual void handleMessage(Actor::IMessage const* msg) override;
};

