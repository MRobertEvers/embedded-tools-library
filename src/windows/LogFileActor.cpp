#include "LogFileActor.h"
#include "IPoolMessage.h"

#include <string>
#include <fstream>
#include <iostream>

bool
LogFileActor::handle_accepts(pvt::IMessage const* const msg) const
{
	return msg->sig == 2 ;
}

void
LogFileActor::handle_process_one(pvt::IMessage const* const msg)
{


	auto evt = static_cast<pvt::IPoolMessage const*>(msg);

	std::ofstream file("dump.txt");

	std::string sz(static_cast<char const*>(evt->data()), evt->size());
	std::cout << "[LogFileActor] " << sz << '\n';

	file << std::string((char*)evt->data(), evt->size()) << '\n';
}