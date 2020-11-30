#pragma once
#include "ActorModel.h"
#include "Dispatcher.h"

class CLIActor : public Actor::ActorModel 
{
public:
	CLIActor(Actor::IActorQueue* q, Actor::Dispatcher* disp) : Actor::ActorModel(q), dispatcher(disp)
	{

	}

	bool subscribed(int msgType);

protected:
	void handleMessage(Actor::IMessage const* msg);

private:
	Actor::Dispatcher* dispatcher;
};

