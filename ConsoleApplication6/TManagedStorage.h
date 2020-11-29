#pragma once
#include "ControlBlock.h"

namespace Pool::Managed
{
template <typename T, typename CtrlBlk = ControlBlock>
class TManagedStorage
{
public:
	T object;
	CtrlBlk control;
};
}

