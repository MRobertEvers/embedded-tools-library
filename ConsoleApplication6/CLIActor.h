#pragma once
#include "ActorModel.h"
#include "MessageHandle.h"
#include "Dispatcher.h"

class CLIActor : public Actor::ActorModel 
{
public:
	CLIActor(Actor::IActorQueue* q, Dispatcher* disp) : Actor::ActorModel(q), dispatcher(disp)
	{

	}

	bool subscribed(int msgType);

protected:
	void handleMessage(Actor::MessageHandle msg);

private:
	Dispatcher* dispatcher;
};

