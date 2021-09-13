#include "IMessage.h"

/**
 * Declare your message types using,
 * template <> struct MessageType<TypeId> { TypeName Type };
 *
 * Then provide a handler that has a 'handle_message(TypeName const* msg)' function.
 *
 * Example Usage
 *
 * e.g. I want a message of type 2.
 * class MyMessageType : public IMessage { ... }
 * template <> struct MessageType<2> : DeclareAs<MyMessageType> {}
 *
 * struct Handler
 * {
 *     void handle_message(MyMessageType const* msg);
 * }
 *
 * int main()
 * {
 *     Handler handler;
 *     MyMessageType msg;
 *     msg.type = 2;
 *     handle_message<2>(&handler, &msg);
 * }
 *
 */

template<int Type>
struct MessageType
{
};

template<typename T>
struct DeclareAs
{
	using Type = T;
};

// Recursive definition
template<typename Handler, int IndexTypeId, int... OtherTypeIds>
struct HandleMessage
{
	static constexpr bool call(Handler& handler, pvt::IMessage const* msg) noexcept
	{
		if( msg->sig == IndexTypeId )
			handler.handle_message(static_cast<typename MessageType<IndexTypeId>::Type const*>(msg));
		return msg->sig == IndexTypeId || HandleMessage<Handler, OtherTypeIds...>::call(handler, msg);
	}
};

// Base of the recursion.
template<typename Handler, int IndexTypeId>
struct HandleMessage<Handler, IndexTypeId>
{
	static constexpr bool call(Handler& handler, pvt::IMessage const* msg) noexcept
	{
		if( msg->sig == IndexTypeId )
			handler.handle_message(static_cast<typename MessageType<IndexTypeId>::Type const*>(msg));
		return msg->sig == IndexTypeId;
	}
};

template<int... TypeIds, typename Handler>
constexpr bool
handle_message(Handler& handler, pvt::IMessage const* msg) noexcept
{
	return HandleMessage<Handler, TypeIds...>::call(handler, msg);
}
