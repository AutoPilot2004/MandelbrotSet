#include "Renderer.h"

#include <glad/glad.h>

namespace
{
	bool bufferbit_check(Lib::Renderer::BufferBit mask, Lib::Renderer::BufferBit value)
	{
		return (mask & value) == value;
	}

	GLbitfield bufferbit_native_to_gl(Lib::Renderer::BufferBit mask)
	{
		GLbitfield bitfield = 0;

		if (bufferbit_check(mask, Lib::Renderer::BufferBit::COLOR_BUFFER_BIT))
			bitfield |= GL_COLOR_BUFFER_BIT;
		if (bufferbit_check(mask, Lib::Renderer::BufferBit::DEPTH_BUFFER_BIT))
			bitfield |= GL_DEPTH_BUFFER_BIT;

		return bitfield;
	}
}

namespace Lib
{
	namespace Renderer
	{
		void clear(BufferBit mask)
		{
			glClear(bufferbit_native_to_gl(mask));
		}

		void clear_color(float red, float green, float blue, float alpha)
		{
			glClearColor(red, green, blue, alpha);
		}

		void set_viewport(int x, int y, uint16_t width, uint16_t height)
		{
			glViewport(x, y, width, height);
		}

		void render_triangles(int32_t first, size_t count)
		{
			glDrawArrays(GL_TRIANGLES, first, count);
		}
	}
}