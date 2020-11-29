#pragma once

#include "IMultiPoolSource.h"
#include "IManagedStorage.h"

namespace Pool
{
template <typename Interface>
using IManagedMultiPoolSource = IMultiPoolSource<Managed::IManagedStorage<Interface>>;
}
