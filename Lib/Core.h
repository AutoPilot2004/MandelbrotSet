#pragma once

#include <expected>

namespace Lib
{
	enum class CoreError
	{
		INIT_FAIL
	};

	std::expected<void, CoreError> init();
	void destroy();

	[[noreturn]] void fatal_error(const char* message);

	double get_current_time();

	template<typename T, typename E, typename F>
		requires std::is_invocable_v<F>
	std::expected<T, E> expected_from_invocable(F&& f)
	{
		return std::expected<void, E>().transform(std::forward<F>(f));
	}

	template<typename T, typename E, typename F>
		requires std::is_invocable_r_v<T, F, E>
	T value_or_else(std::expected<T, E>&& expected, F&& fn)
	{
		if (expected)
			return std::move(*expected);

		return std::forward<F>(fn)(expected.error());
	}
}