#pragma once
#include "IActor.h"
#include "TStaticArrayList.h"
#include "send_message.h"

template <unsigned int MaxActors>
class Dispatcher : public pvt::IRouter
{
public:
	Dispatcher() : actors_() { }

	void subscribe(pvt::IRouter* router)
	{
		actors_.emplace_back(router);
	}

private:
	pvt::TStaticArrayList<pvt::IRouter*, MaxActors> actors_;

	// Inherited via IActor
	virtual bool handle_accepts(pvt::IMessage const* const msg) const override
	{
		return true;
	}

	virtual bool handle_post_message(pvt::IMessage const* const msg) override
	{
		//auto recv_end = std::stable_partition(
		//	begin(actors_), end(actors_),
		//	[&msg](auto actor) {return actor->accepts(msg); });

		for( auto i = 0; i < actors_.size(); ++i )
		{
			send_message(*actors_.at(i), msg);
		}

		return true;
	}
};

