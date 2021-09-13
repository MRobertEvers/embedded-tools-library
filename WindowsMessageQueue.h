#pragma once
#include "IActorQueue.h"
#include <condition_variable>

#include <mutex>
#include <vector>

class WindowsMessageQueue : public pvt::IActorQueue
{
public:
	// Inherited via IActorQueue
	virtual bool handle_put_message(pvt::IMessage const* msg) override;
	virtual pvt::IMessage const* handle_get_message() override;

private:
	std::condition_variable m_signal;
	std::mutex m_mutex;

	std::vector<pvt::IMessage const*> m_q;
};