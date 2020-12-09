#include "WindowsQueue.h"

void WindowsQueue::handle_put_message(Actor::IMessage const* msg)
{
   std::unique_lock lock(mutex_);

   if( q_.size() < 10 )
   {
      q_.push_back(msg);
      signal_.notify_one();
   }
}

Actor::IMessage const* WindowsQueue::handle_get_message()
{
   std::unique_lock lock(mutex_);

   while( q_.size() == 0 )
   {
      // release lock as long as the wait and reaquire it afterwards.
      signal_.wait(lock);
   }

   auto item = q_.back();
   q_.pop_back();
   return item;
}
