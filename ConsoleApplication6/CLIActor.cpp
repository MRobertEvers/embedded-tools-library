#include "CLIActor.h"
#include "TMessage.h"
#include <iostream>

bool CLIActor::handle_accepts(Actor::IMessage const* const msg) const
{
	return true;
}

void CLIActor::handle_process_one(Actor::IMessage const* const msg)
{
	std::cout << "msg recved\n";
	switch( msg->type() )
	{
	case 2:
		auto data_msg = static_cast<IDataMessage const*>(msg);
		std::string sz((char const*)data_msg->data(), data_msg->size());
		std::cout << sz << '\n';
	}
}
