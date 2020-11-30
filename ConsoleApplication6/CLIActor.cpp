#include "CLIActor.h"

#include <iostream>

bool CLIActor::subscribed(int msgType)
{
	return msgType == 1;
}

void CLIActor::handleMessage(Actor::IMessage const* msg)
{
	std::string sz(static_cast<char const*>(msg->data()), msg->size());

	std::cout << "[CLIActor] " << sz << '\n';

	if( sz._Starts_with("log ") )
	{
		dispatcher->sendMessage(2, 1, 2, (char*)msg->data(), msg->size());
	}
}