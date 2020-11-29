#pragma once

template <typename T, size_t Size>
class TArray
{
public:
	size_t size()
	{
		return Size;
	}

	T* data()
	{
		return m_data;
	}

private:
	T m_data[Size];
};

