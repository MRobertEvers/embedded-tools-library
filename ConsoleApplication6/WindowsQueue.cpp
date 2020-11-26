#include "WindowsQueue.h"


void WindowsQueue::putMessage(Actor::IMessage* msg)
{
   std::unique_lock lock(m_mutex);

   if( m_q.count() < m_q.capacity() )
   {
      m_q.push(msg);
      m_signal.notify_one();
   }
}

Actor::IMessage* WindowsQueue::getMessage()
{
   std::unique_lock lock(m_mutex);

   while( m_q.count() == 0 )
   {
      // release lock as long as the wait and reaquire it afterwards.
      m_signal.wait(lock);
   }

   return m_q.pop();
}
