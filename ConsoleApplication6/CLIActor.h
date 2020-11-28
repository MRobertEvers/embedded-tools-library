#pragma once
#include "ActorModel.h"
#include "MessageHandle.h"

#include <string>
#include <iostream>

class CLIActor : public Actor::ActorModel 
{
public:
	CLIActor(Actor::IActorQueue* q) : Actor::ActorModel(q)
	{

	}


protected:
	void handleMessage(Actor::MessageHandle msg)
	{
		std::string sz(static_cast<char*>(msg->data()), msg->size());

		std::cout << sz;
	}
};

