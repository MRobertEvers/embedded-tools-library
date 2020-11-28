#include "WindowsQueue.h"


void WindowsQueue::putMessage(Actor::MessageHandle msg)
{
   std::unique_lock lock(m_mutex);

   if( m_q.size() < 10 )
   {
      m_q.push_back(msg);
      m_signal.notify_one();
   }
}

Actor::MessageHandle WindowsQueue::getMessage()
{
   std::unique_lock lock(m_mutex);

   while( m_q.size() == 0 )
   {
      // release lock as long as the wait and reaquire it afterwards.
      m_signal.wait(lock);
   }

   auto item = m_q.back();
   m_q.pop_back();
   return item;
}
