#pragma once
#include "TManaged.h"

#include "IMessage.h"

#include "SourceMap.h"

#include <iostream>

namespace Actor
{
class MessageHandle
{
public:
	MessageHandle(Actor::IMessage* msg, Pool::Managed::TManaged<Pool::MultiPool::SourceMap> srcInfo)
		: m_pMessage(msg), m_SourceMap(srcInfo)
	{
		std::cout << "MessageHandle()\n";
	};

	~MessageHandle()
	{
		std::cout << "~MessageHandle()\n";
	}

	bool ok()
	{
		return m_SourceMap.ok() && m_pMessage != nullptr;
	}

	Actor::IMessage* operator->()
	{
		return m_pMessage;
	};

private:
	Actor::IMessage* m_pMessage;
	Pool::Managed::TManaged<Pool::MultiPool::SourceMap> m_SourceMap;
};
}