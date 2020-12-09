#pragma once


namespace Actor
{
class IRouter;
class IMessage;
void send_message(IRouter* router, IMessage const* const msg);
}
