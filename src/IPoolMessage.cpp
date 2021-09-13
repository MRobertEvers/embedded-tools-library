#include "IPoolMessage.h"
#include "MessagePool.h"
namespace pvt 
{
void 
IPoolMessage::acquire() const
{
	++ref_cnt_;
}

void 
IPoolMessage::release() const
{
	if( ref_cnt_ > 0 )
	{
		--ref_cnt_;
		if( ref_cnt_ == 0 )
		{
			src_->release(this);
		}
	}
}
}