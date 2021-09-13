#pragma once

#include "TQueue.h"
namespace pvt
{
template<typename T, unsigned int Size>
class TStaticQueue : public TQueue<T>
{
public:
	TStaticQueue()
		: TQueue<T>(buf_, Size){};

	virtual ~TStaticQueue() {}

private:
	T buf_[Size];
};
} // namespace pvt