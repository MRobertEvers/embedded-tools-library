#pragma once
#include "IActor.h"

class LogFileActor : public pvt::IActor
{
public:
	LogFileActor(pvt::IActorQueue* q)
		: pvt::IActor(q)
	{
	}

	// Inherited via ActorModel
	virtual bool handle_accepts(pvt::IMessage const* const msg) const override;
	virtual void handle_process_one(pvt::IMessage const* const msg) override;
};