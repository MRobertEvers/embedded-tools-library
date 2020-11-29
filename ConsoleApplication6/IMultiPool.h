#pragma once
template <typename T>
class IMultiPool
{
public:	
	virtual T* acquire(size_t size) = 0;
	virtual void release(T const* item, size_t size) = 0;
};

