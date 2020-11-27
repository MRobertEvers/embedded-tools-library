#pragma once
namespace Pool::MultiPool
{
class SourceMap
{
public:
	SourceMap() : source(-1)
	{
	};

	SourceMap(int source) : source(source)
	{

	};

	void prepare(int src)
	{
		source = src;
	};

	int getSource() const
	{
		return source;
	};

private:
	int source;
};

}
