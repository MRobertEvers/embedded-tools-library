#pragma once
#include "ActorModel.h"

class LogFileActor : public Actor::ActorModel
{
public:
	LogFileActor(Actor::IActorQueue* q) : Actor::ActorModel(q)
	{

	}

	// Inherited via ActorModel
	virtual bool subscribed(int msgType) override;
	virtual void handleMessage(Actor::IMessage* msg) override;
};

