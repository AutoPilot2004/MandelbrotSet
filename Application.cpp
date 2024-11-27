#include "Application.h"

#include <Mandelbrot_Set/Core.h>
#include <Mandelbrot_Set/VertexArray.h>
#include <Mandelbrot_Set/ShaderProgram.h>
#include <Mandelbrot_Set/RenderState.h>
#include <Mandelbrot_Set/Texture.h>
#include <Mandelbrot_Set/Window.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

auto Application::run(int width, int height, const char* title) -> std::expected<int, Error>
{
	if (!Lib::init()) return std::unexpected<Error>({ 1, "Couldn't initialize lib!" });

	{
		auto window = Lib::WindowSystem::Window::create(width, height, title);
		if (!window) return std::unexpected<Error>({ 2, "Couldn't create window!" });
		window->make_context_current();

		auto program = Lib::ShaderProgram::create("assets/shaders/vert.vert", "assets/shaders/frag.frag");
		if (!program) std::unexpected<Error>({ 3, "Couldn't create shader program!" });

		Lib::VertexArray va;

		int w, h, ch;
		unsigned char* data = stbi_load("assets/textures/map_2.png", &w, &h, &ch, 0);
		if (!data) std::unexpected<Error>({ 4, "Couldn't load image!" });

		Lib::Texture tex(data, w);
		tex.bind_unit(0);

		stbi_image_free(data);

		program->uniform1i(0, 0);

		Lib::Renderer::clear_color(0.0f, 0.0f, 0.0f, 1.0f);

		double zoom = 1.0;

		double xPos = 0.0, yPos = 0.0;
		double prevXPos = xPos, prevYPos = yPos;
		double xCoord = xPos, yCoord = yPos;

		program->uniform2d(1, xCoord, yCoord);
		program->uniform1d(2, zoom);
		program->uniform2d(3, xPos, yPos);
		program->uniform2i(4, width, height);

		window->set_cursor_pos_callback([&](double x, double y)
			{
				prevXPos = xPos;
				prevYPos = yPos;

				xPos = x;
				yPos = 1000.0 - y;

				xCoord += ((xPos - prevXPos) / zoom);
				yCoord += ((yPos - prevYPos) / zoom);

				program->uniform2d(1, xCoord, yCoord);
				program->uniform2d(3, xPos, yPos);
			}
		);

		window->set_framebuffer_size_callback([&](int width, int height)
			{
				Lib::Renderer::set_viewport(0, 0, width, height);
			}
		);

		auto lastTime = Lib::get_current_time();

		constexpr double speed = 2.5;

		va.bind();
		program->bind();

		while (!window->should_close()) {
			auto now = Lib::get_current_time();
			auto dT = now - lastTime;
			lastTime = now;

			//Useless
			Lib::Renderer::clear(Lib::Renderer::BufferBit::COLOR_BUFFER_BIT);

			program->uniform1d(2, zoom *= std::pow(speed, dT));

			Lib::Renderer::render_triangles(0, 3);

			window->swap_buffers();
			Lib::WindowSystem::poll_events();
		}
	}

	Lib::destroy();

	return 0;
}