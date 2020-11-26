#pragma once
#include <type_traits>

namespace Actor
{
template <size_t Size>
class TMessage
{
public:

	template<typename T, typename... Args>
	void construct(Args&&... args)
	{
		static_assert(std::is_trivially_destructible<T>::value);
		static_assert(sizeof(T) <= Size);

		new (m_pBuf) T(std::forward<Args>(args)...);
	}

private:
	char m_pBuf[Size];
};

}
