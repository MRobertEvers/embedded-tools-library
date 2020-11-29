#pragma once
#include "ControlBlock.h"
#include "IManagedStorage.h"

namespace Pool::Managed
{
template <typename T, typename CtrlBlk = ControlBlock>
class TManagedStorage : public IManagedStorage<T, CtrlBlk>
{
public:
	virtual T* getPtr() override
	{
		return &object;
	};

	virtual CtrlBlk* getCtrl() override
	{
		return &control;
	};

private:
	T object;
	CtrlBlk control;
};
}

