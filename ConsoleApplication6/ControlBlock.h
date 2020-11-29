#pragma once
namespace Pool::Managed
{
class ControlBlock
{
public:
	int incRef()
	{
		return ++m_count;
	};

	int decRef()
	{
		if( m_count > 0 )
		{
			m_count -= 1;
		}
		return m_count;
	};

	int count()
	{
		return m_count;
	}
private:
	unsigned short m_count = 0;
};

}
