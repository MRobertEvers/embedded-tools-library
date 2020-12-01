#include "LogFileActor.h"

#include <string>
#include <fstream>
#include <iostream>

bool LogFileActor::subscribed(int msgType)
{
	return msgType == 2;
}

void LogFileActor::handleMessage(Actor::IMessage const* msg)
{
	std::ofstream file("dump.txt");

	std::string sz(static_cast<char const*>(msg->data()), msg->size());
	std::cout << "[LogFileActor] " << sz << '\n';

	file << sz << '\n';
}
