#pragma once
#include "IMessage.h"
namespace pvt
{
class MessagePool;
class IPoolMessage : public pvt::IMessage
{
public:
	virtual unsigned int size() const = 0;
	virtual unsigned short data_size() const { return data_size_; };
	virtual void const* data() const = 0;

	virtual void prepare(MessagePool* src, unsigned int type, void const* data, unsigned int size) = 0;

protected:
	MessagePool* src_;
	unsigned short data_size_ = 0;

	virtual void acquire() const override;

	virtual void release() const override;

private:
	mutable unsigned char ref_cnt_ = 0;
};
} // namespace pvt