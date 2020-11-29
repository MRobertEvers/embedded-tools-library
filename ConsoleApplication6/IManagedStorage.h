#pragma once
#include "ControlBlock.h"
namespace Pool::Managed
{
template <typename T, typename CtrlBlk = ControlBlock>
class IManagedStorage
{
public:
	virtual T* getPtr() = 0;
	virtual CtrlBlk* getCtrl() = 0;
};
}
