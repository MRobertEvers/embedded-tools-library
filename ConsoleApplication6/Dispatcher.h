#pragma once
#include "IMessagePool.h"
#include "ActorModel.h"
#include "ControlBlock.h"

#include "TStaticArrayList.h"

namespace Actor
{
class Dispatcher
{
public:
	Dispatcher(IMessagePool* pool)
		: actors_(), ctrls_(), pool_(pool)
	{

	};

	void sendMessage(int type, void const* data, size_t size);

	void registerActor(ActorModel* act)
	{
		actors_.emplace_back(act);
	}

private:
	TStaticArrayList<Actor::ActorModel*, 10> actors_;
	TStaticArrayList<Pool::Managed::ControlBlock, 100> ctrls_;

	IMessagePool* pool_;
};
}

