#include "CLIActor.h"
#include "send_message.h"
#include "IPoolMessage.h"
#include <iostream>

bool
CLIActor::handle_accepts(pvt::IMessage const* const msg) const
{
	return msg->sig == 1 || msg->sig == 3;
}

void
CLIActor::handle_process_one(pvt::IMessage const* const m)
{
	if( m->sig == 3 )
	{
		std::cout << "[CLIActor] " << "timer fired" << '\n';
		return;
	}

	auto msg = static_cast<pvt::IPoolMessage const*>(m);

	std::string sz(static_cast<char const*>(msg->data()), msg->size());

	std::cout << "[CLIActor] " << sz << '\n';

	if( sz._Starts_with("log ") )
	{
		send_message(dispatcher, m);
	}
}