#pragma once

#include <cstdint>
#include <utility>

namespace Lib
{
	namespace Renderer
	{
		using BufferBitField = uint8_t;

		enum BufferBit : BufferBitField
		{
			COLOR_BUFFER_BIT = 1 << 0,
			DEPTH_BUFFER_BIT = 1 << 1
		};

		void clear(BufferBitField mask);
		void clear_color(float red, float green, float blue, float alpha);

		void set_viewport(int x, int y, uint16_t width, uint16_t height);

		void render_triangles(int32_t first, size_t count);
	}
}