#pragma once
#include "IControlBlock.h"

namespace pvt::Managed
{
class ControlBlock : public IControlBlock
{
public:
	int inc_ref() { return ++count_; };

	int dec_ref()
	{
		if( count_ > 0 )
		{
			count_ -= 1;
		}
		return count_;
	};

	int count() { return count_; }

private:
	unsigned short count_ = 0;
};

} // namespace pvt::Managed
