#pragma once
#include "IControlBlock.h"

namespace Pool::Managed
{
class ControlBlock : public IControlBlock
{
public:
	int incRef()
	{
		return ++count_;
	};

	int decRef()
	{
		if( count_ > 0 )
		{
			count_ -= 1;
		}
		return count_;
	};

	int count()
	{
		return count_;
	}
private:
	unsigned short count_ = 0;
};

}
