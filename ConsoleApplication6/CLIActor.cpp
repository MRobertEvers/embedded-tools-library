#include "CLIActor.h"

#include <iostream>

bool CLIActor::subscribed(int msgType)
{
	return msgType == 1;
}

void CLIActor::handleMessage(Actor::IMessage const* msg)
{
	std::string sz((char*)msg->data(), msg->size());

	std::cout << "[CLIActor] " << sz << '\n';

	if( sz._Starts_with("log ") )
	{
		dispatcher->sendMessage(2, msg->data(), msg->size());
	}
}