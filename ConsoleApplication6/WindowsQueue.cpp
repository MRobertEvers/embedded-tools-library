#include "WindowsQueue.h"


void WindowsQueue::putMessage(Actor::MessageHandle msg)
{
   std::unique_lock lock(m_mutex);

   if( q_.size() < 10 )
   {
      q_.push_back(msg);
      m_signal.notify_one();
   }
}

Actor::MessageHandle WindowsQueue::getMessage()
{
   std::unique_lock lock(m_mutex);

   while( q_.size() == 0 )
   {
      // release lock as long as the wait and reaquire it afterwards.
      m_signal.wait(lock);
   }

   auto item = q_.back();
   q_.pop_back();
   return item;
}
