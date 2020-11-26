#pragma once

#include "TPool.h"
#include "TMessage.h"

namespace Actor
{
class MessagePool : public Pool::TPool<TMessage<32>>
{

};
}

