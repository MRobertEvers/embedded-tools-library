#pragma once

#include "IPool.h"
#include "TContiguousPoolBuffer.h"
#include "TStack.h"

#include <array>

namespace pvt
{
template<typename Interface, typename T = Interface>
class TContiguousPool : public IPool<Interface>
{
public:
	template<unsigned int Size>
	TContiguousPool(std::array<T, Size>* buffer, std::array<int, Size>* control)
		: buf_(buffer->data())
		, q_(control->data(), Size)
	{
		for( int i = 0; i < Size; i++ )
		{
			q_.push(i);
		}
	};

	template<unsigned int Size>
	TContiguousPool(Resource::TContiguousPoolBuffer<T, Size>* resource)
		: TContiguousPool(&resource->buffer, &resource->control){};

	virtual ~TContiguousPool() {}

	Interface* acquire() override;
	void release(Interface const* item) override;

	int size() override { return q_.capacity(); }

	int get_item_index(Interface const* item);

private:
	int acquire_next_index();

	TStack<int> q_;
	T* buf_;
};

template<typename Interface, typename T>
inline Interface*
TContiguousPool<Interface, T>::acquire()
{
	// TODO: Synchronized version lock here.
	auto next = acquire_next_index();
	if( next == -1 )
	{
		return nullptr;
	}
	else
	{
		return &buf_[next];
	}
}

template<typename Interface, typename T>
inline void
TContiguousPool<Interface, T>::release(Interface const* item)
{
	q_.push(get_item_index(item));
}

template<typename Interface, typename T>
inline int
TContiguousPool<Interface, T>::get_item_index(Interface const* item)
{
	return (static_cast<T const*>(item) - buf_);
}

template<typename Interface, typename T>
inline int
TContiguousPool<Interface, T>::acquire_next_index()
{
	if( q_.count() == 0 )
	{
		return -1;
	}
	else
	{
		auto item = q_.peek();
		q_.pop();
		return item;
	};
}
} // namespace pvt