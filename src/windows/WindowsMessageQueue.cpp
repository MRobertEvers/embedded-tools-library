#include "WindowsMessageQueue.h"

bool
WindowsMessageQueue::handle_put_message(pvt::IMessage const* msg)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	if( m_q.size() < 10 )
	{
		m_q.push_back(msg);
		m_signal.notify_one();

		return true;
	}

	return false;
}

pvt::IMessage const*
WindowsMessageQueue::handle_get_message()
{
	std::unique_lock<std::mutex> lock(m_mutex);

	while( m_q.size() == 0 )
	{
		// release lock as long as the wait and reaquire it afterwards.
		m_signal.wait(lock);
	}

	auto item = m_q.back();
	m_q.pop_back();

	return item;
}