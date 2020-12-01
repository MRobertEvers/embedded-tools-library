#pragma once

class IControlBlock
{
public:
	virtual int incRef() = 0;
	virtual int decRef() = 0;
	virtual int count() = 0;
};

