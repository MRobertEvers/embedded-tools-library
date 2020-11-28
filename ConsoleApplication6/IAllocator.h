#pragma once

template <typename T>
class IAllocator
{
public:
	virtual T* allocate() = 0;
	virtual void free(T* arg) = 0;

	virtual int size() = 0;

	virtual int numAllocated() = 0;
};

