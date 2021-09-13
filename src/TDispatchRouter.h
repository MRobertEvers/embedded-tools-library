#pragma once

#include "IRouter.h"
#include "TStaticArrayList.h"

#include <algorithm>

namespace pvt
{
template<unsigned int MaxActors>
class TDispatchRouter : public IRouter
{
public:
	virtual ~TDispatchRouter(){};

	void subscribe(IRouter* router);

	virtual void accepts(IMessage const* msg) override;
	virtual void receive(IMessage const* msg) override;

private:
	TStaticArrayList<IRouter*, MaxActors> actors_;
};

template<unsigned int MaxActors>
inline void 
TDispatchRouter<MaxActors>::subscribe(IRouter* router)
{
	actors_.emplace_back(router);
}

template<unsigned int MaxActors>
inline void 
TDispatchRouter<MaxActors>::accepts(IMessage const* msg)
{
	return true;
}

template<unsigned int MaxActors>
inline void 
TDispatchRouter<MaxActors>::receive(IMessage const* msg)
{
	// TODO: Maybe not the best to do this here, but it saves some memory...
	auto receiveEnd = std::stable_partition(
		begin(actors_), end(actors_),
		[&msg](auto actor) { return actor->accepts(msg); });

	for( auto iter = begin(actors_); iter != receiveEnd; ++iter )
	{
		send_message(*iter, msg);
	}
}
}

