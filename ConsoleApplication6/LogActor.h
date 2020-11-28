#pragma once
#include "ActorModel.h"

#include <iostream>

namespace Actor
{
class LogActor : public Actor::ActorModel
{
public:
	void handleMessage(Actor::MessageHandle msg)
	{
		std::string sz(static_cast<char*>(msg->data()), msg->size());

		std::cout << sz;
	}
};
}

