#pragma once
#include "IPoolResource.h"

namespace Pool
{
template<typename T>
class TPoolObjectHandle
{
public:
	TPoolObjectHandle(IPoolResource<T>* resource): m_pItem(resource->allocate()), m_pResource(resource)
	{

	}

	~TPoolObjectHandle()
	{
		m_pResource->free(m_pItem);
	}

	T* operator->()
	{
		return m_pItem;
	}

private:
	T* m_pItem;
	IPoolResource<T>* m_pResource;
};
}

