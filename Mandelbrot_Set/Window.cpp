#include "Window.h"

#include <stdexcept>

#include <GLFW/glfw3.h>

#include "Core.h"

#define SET_USER_POINTER() glfwSetWindowUserPointer(m_handle, this)
#define GET_USER_POINTER() static_cast<Window*>(glfwGetWindowUserPointer(win))

#define CALL_MEMBER_FN(fn, ...) auto& func = GET_USER_POINTER()->fn;         \
							    do { if (func) func(__VA_ARGS__); } while(0)

namespace Lib
{
	namespace WindowSystem
	{
		Window::Window(GLFWwindow* handle) noexcept
			: m_handle(handle)
		{
			SET_USER_POINTER();
			inject_callbacks();
		}

		Window::~Window()
		{
			if (m_handle) glfwDestroyWindow(m_handle);
		}

		std::expected<Window, Error> Window::create(int width, int height, const char* title, bool visible) noexcept
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_VISIBLE, visible);

			auto* handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
			if (!handle) return std::unexpected(Error::WINDOW_CREATION_FAILED);

			return expected_from_invocable<Window, Error>([=]() {
				return Window(handle);
				});
		}

		void Window::make_context_current() const
		{
			glfwMakeContextCurrent(m_handle);
		}

		bool Window::should_close() const
		{
			return glfwWindowShouldClose(m_handle);
		}

		void Window::swap_buffers() const
		{
			glfwSwapBuffers(m_handle);
		}

		void Window::set_cursor_pos_callback(WindowCursorCallback callback)
		{
			m_cursorPosCallback = std::move(callback);
		}

		void Window::set_framebuffer_size_callback(FramebufferSizeCallback callback)
		{
			m_framebufferSizeCallback = std::move(callback);
		}

		void Window::inject_callbacks() const
		{
			glfwSetCursorPosCallback(m_handle, cursor_pos_callback);
			glfwSetFramebufferSizeCallback(m_handle, framebuffer_size_callback);
		}

		void Window::cursor_pos_callback(GLFWwindow* win, double x, double y)
		{
			CALL_MEMBER_FN(m_cursorPosCallback, x, y);
		}

		void Window::framebuffer_size_callback(GLFWwindow* win, int width, int height)
		{
			CALL_MEMBER_FN(m_framebufferSizeCallback, width, height);
		}

		void poll_events()
		{
			glfwPollEvents();
		}
	}
}