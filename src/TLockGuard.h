#pragma once
namespace pvt 
{
template <typename Mutex>
class TLockGuard
{
public:
	TLockGuard(Mutex& m) : m_(m)
	{
		m_.lock();
	}

	~TLockGuard()
	{
		m_.unlock();
	}

private:
	Mutex& m_;
};
}