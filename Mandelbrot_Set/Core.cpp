#include "Core.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Lib
{
	bool init()
	{
		if (!glfwInit()) return false;

		auto tmpWin = WindowSystem::Window::create(1, 1, "", false);
		if (!tmpWin) return false;

		tmpWin->make_context_current();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;

		return true;
	}

	void destroy()
	{
		glfwTerminate();
	}

	void fatal_error(const char* message, int errorCode)
	{
		std::cout << message << std::endl;
		destroy();
		std::cout << "Press enter to exit...";
		std::cin.get();
		std::exit(errorCode);
	}

	double get_current_time()
	{
		return glfwGetTime();
	}
}