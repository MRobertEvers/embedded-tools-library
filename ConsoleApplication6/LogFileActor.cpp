//#include "LogFileActor.h"
//
//#include <string>
//#include <fstream>
//#include <iostream>
//
//bool LogFileActor::subscribed(int msgType)
//{
//	return msgType == 2;
//}
//
//void LogFileActor::handleMessage(ManagedMessagePtr msg)
//{
//	std::ofstream file("dump.txt");
//
//	std::string sz(static_cast<char*>(msg->data()), msg->size());
//	std::cout << "[LogFileActor] " << sz << '\n';
//
//	file << std::string((char*)msg->data(), msg->size()) << '\n';
//}
