#pragma once
#include "IActor.h"
#include "TStaticArrayList.h"
#include "send_message.h"

template <size_t MaxActors>
class Dispatcher : public Actor::IRouter
{
public:
	Dispatcher() : actors_() { }

	void subscribe(Actor::IRouter* router)
	{
		actors_.emplace_back(router);
	}

private:
	TStaticArrayList<Actor::IRouter*, MaxActors> actors_;

	// Inherited via IActor
	virtual bool handle_accepts(Actor::IMessage const* const msg) const override
	{
		return true;
	}

	virtual void handle_post_message(Actor::IMessage const* const msg) override
	{
		//auto recv_end = std::stable_partition(
		//	begin(actors_), end(actors_),
		//	[&msg](auto actor) {return actor->accepts(msg); });

		for( auto i = 0; i < actors_.size(); ++i )
		{
			send_message(*actors_.at(i), msg);
		}
	}
};

