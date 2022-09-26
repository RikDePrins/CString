#pragma once
#include <type_traits>  // std::is_convertible
#include <cassert>		// assert
#include <climits>		// INT_MIN

namespace raptor
{
	template <typename CString>
	[[nodiscard]] int GetIntFromCString(const CString cStr, bool& isAnInt, bool& isOutOfRange) noexcept
	{
		// Won't allow std::nullptr_t
		static_assert(std::is_convertible<CString, const char*>::value, "C-string expected");

		// DEBUG: Assures cStr isn't a nullptr
		assert(cStr != nullptr && "C-string not allowed to be nullptr");

		// Initially error flags are set to no errors
		isAnInt = true;
		isOutOfRange = false;

		// If cStr is empty, it doesn't contain an int
		if (cStr[0] == '\0')
		{
			isAnInt = false;
			return 0;
		}

		int num{ 0 };
		int idx{ 0 };

		// 1 = positive
		// -1 = negative
		int sign{ 1 };

		// If first char is minus sign, sign is set to negative
		if (cStr[0] == '-')
		{
			sign = -1;
			++idx;
		}

		// Loops until a zero-terminator is found
		for (; cStr[idx] != '\0'; ++idx)
		{
			// If cStr[idx] isn't between the character range representing 0 to 9, 
			// it doesn't contain purely an int
			if (cStr[idx] < '0' || cStr[idx] > '9')
			{
				isAnInt = false;
				return 0;
			}

			const int tempNum{ num };

			// Decrements num to push back digit at cStr[idx]
			// Decrement because -2147483648 is within range while 2147483648 isn't
			num = num * 10 - cStr[idx] + '0';

			// If num is greater than tempNum, the number inside cStr is out of int range
			if (num > tempNum)
			{
				isOutOfRange = true;
				return 0;
			}
		}

		// cStr contains 2147483648
		if (sign == 1 && num == INT_MIN)
		{
			isOutOfRange = true;
			return 0;
		}

		// Return opposite sign * num
		return -sign * num;
	}
}