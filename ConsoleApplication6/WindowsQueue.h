//#pragma once
//#include "IActorQueue.h"
//#include "TStaticQueue.h"
//#include "MessageMultiPool.h"
//
//#include <mutex>
//#include <condition_variable>
//#include <vector>
//
//class WindowsQueue : public Actor::IActorQueue
//{
//public:
//	// Inherited via IActorQueue
//	virtual void putMessage(ManagedMessagePtr msg) override;
//	virtual ManagedMessagePtr getMessage() override;
//
//private:
//	std::condition_variable m_signal;
//	std::mutex m_mutex;
//
//	std::vector<ManagedMessagePtr> m_q;
//	//TStaticQueue<Actor::IMessage*, 10> m_q;
//};
//
