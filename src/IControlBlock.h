#pragma once
namespace pvt
{
class IControlBlock
{
public:
	virtual int inc_ref() = 0;
	virtual int dec_ref() = 0;
	virtual int count() = 0;
};
} // namespace pvt