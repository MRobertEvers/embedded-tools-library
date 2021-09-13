#pragma once
#include "IActor.h"
#include "Dispatcher.h"
#include "IMessage.h"

class CLIActor : public pvt::IActor
{
public:
	CLIActor(pvt::IActorQueue* q, pvt::IRouter* disp)
		: pvt::IActor(q)
		, dispatcher(disp)
	{
	}


	// Inherited via ActorModel
	virtual bool handle_accepts(pvt::IMessage const* const msg) const override;
	virtual void handle_process_one(pvt::IMessage const* const msg) override;

private:
	pvt::IRouter* dispatcher;
};