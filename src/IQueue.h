#pragma once
namespace pvt
{
template<typename T>
class IQueue
{
public:
	virtual bool push(const T& item) = 0;
	virtual T pop() = 0;

	virtual unsigned int capacity() const = 0;
	virtual unsigned int count() const = 0;
};
} // namespace pvt