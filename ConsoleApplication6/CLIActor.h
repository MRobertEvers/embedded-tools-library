#pragma once
#include "IActor.h"

class CLIActor : public Actor::IActor
{
public:
	CLIActor(Actor::IActorQueue* q) : Actor::IActor(q) { }
	// Inherited via IActor
	virtual bool handle_accepts(Actor::IMessage const* const msg) const override;
	virtual void handle_process_one(Actor::IMessage const* const msg) override;
};

