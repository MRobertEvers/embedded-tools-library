#pragma once

#include "ControlBlock.h"
#include "IPool.h"

namespace pvt::Managed
{
// TODO: Restrict to pointer types?
template<typename T>
class TSharedPoolPtr
{
public:
	// TODO: I Don't like default constructor.
	TSharedPoolPtr()
		: pool_(nullptr)
		, item_(nullptr)
		, ctrl_(nullptr)
	{
	}

	TSharedPoolPtr(IPool<T>* pool, ControlBlock* ctrl)
		: pool_(pool)
		, item_(pool->acquire())
		, ctrl_(ctrl)
	{
		if( item_ )
		{
			ctrl_->inc_ref();
		}
	}

	TSharedPoolPtr(const TManagedPtr& cpy)
	{
		item_ = cpy.item_;
		pool_ = cpy.pool_;
		ctrl_ = cpy.ctrl_;

		if( item_ )
		{
			ctrl_->inc_ref();
		}
	}

	~TSharedPoolPtr()
	{
		if( item_ != nullptr && ctrl_->count() > 0 )
		{
			auto count = ctrl_->dec_ref();
			if( count == 0 )
			{
				pool_->release(item_);
			}
		}
	}

	T* operator->() { return item_; }

	bool ok() { return item_ != nullptr; }

private:
	IPool<T>* pool_;
	T* item_;
	ControlBlock* ctrl_;
};
} // namespace pvt::Managed
