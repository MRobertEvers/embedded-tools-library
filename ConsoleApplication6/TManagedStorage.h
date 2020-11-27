#pragma once

#include "ControlBlock.h"

namespace Pool::Managed
{
template <typename T>
class TManagedStorage
{
public:
	T object;
	ControlBlock control;
};
}

