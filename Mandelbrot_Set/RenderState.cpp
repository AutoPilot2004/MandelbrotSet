#include "RenderState.h"

#include <glad/glad.h>

static GLbitfield bufferbit_native_to_gl(Lib::Renderer::BufferBitField mask)
{
	GLbitfield bitfield = 0;

	if (mask & Lib::Renderer::BufferBit::COLOR_BUFFER_BIT)
		bitfield |= GL_COLOR_BUFFER_BIT;
	if (mask & Lib::Renderer::BufferBit::DEPTH_BUFFER_BIT)
		bitfield |= GL_DEPTH_BUFFER_BIT;

	return bitfield;
}

namespace Lib
{
	namespace Renderer
	{
		void clear(BufferBitField mask)
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