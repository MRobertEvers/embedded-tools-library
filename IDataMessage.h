#pragma once
#include "IMessage.h"

namespace pvt
{
class IDataMessage : public pvt::IMessage
{
public:
	virtual unsigned int size() const = 0;
	unsigned short data_size() const { return data_size_; };
	virtual void const* data() const = 0;

protected:
	unsigned short data_size_ = 0;
};
} // namespace pvt