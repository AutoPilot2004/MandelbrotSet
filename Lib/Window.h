#pragma once

#include <expected>
#include <functional>

#include "Defines.h"

typedef struct GLFWwindow GLFWwindow;

namespace Lib
{
	namespace WindowSystem
	{
		using WindowCursorCallback    = std::function<void(double, double)>;
		using FramebufferSizeCallback = std::function<void(int, int)>;

		class Window
		{
		public:
			enum class Error
			{
				CREATION_FAILED
			};

		private:
			Window(GLFWwindow* handle) noexcept;

			DELETE_CPY_MOV_OP(Window);

		public:
			~Window();

		public:
			static std::expected<Window, Error> create(int width, int height, const char* title, bool visible = true) noexcept;

		public:
			void make_context_current() const;

			bool should_close() const;

			void swap_buffers() const;

			void set_cursor_pos_callback(WindowCursorCallback callback);
			void set_framebuffer_size_callback(FramebufferSizeCallback callback);

		private:
			void inject_callbacks() const;

			static void cursor_pos_callback(GLFWwindow*, double, double);
			static void framebuffer_size_callback(GLFWwindow*, int, int);

		private:
			GLFWwindow* m_handle = nullptr;

			WindowCursorCallback    m_cursorPosCallback;
			FramebufferSizeCallback m_framebufferSizeCallback;
		};

		void poll_events();
	}
}