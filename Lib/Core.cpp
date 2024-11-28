#include "Core.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Lib
{
	std::expected<void, CoreError> init()
	{
		if (!glfwInit()) return std::unexpected(CoreError::INIT_FAIL);

		auto tmpWin = WindowSystem::Window::create(1, 1, "", false);
		if (!tmpWin) return std::unexpected(CoreError::INIT_FAIL);

		tmpWin->make_context_current();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return std::unexpected(CoreError::INIT_FAIL);

		return {};
	}

	void destroy()
	{
		glfwTerminate();
	}

	void fatal_error(const char* message)
	{
		std::cout << message << std::endl;
		destroy();
		std::cout << "Press enter to exit...";
		std::cin.get();
		std::exit(EXIT_FAILURE);
	}

	double get_current_time()
	{
		return glfwGetTime();
	}
}