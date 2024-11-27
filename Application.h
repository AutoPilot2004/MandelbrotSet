#pragma once

#include <expected>

namespace Application
{
	struct Error
	{
		int code;
		const char* msg;
	};

	auto run(int width, int height, const char* title) -> std::expected<int, Error>;
}