#pragma once

#include <cstdint>
#include <utility>

namespace Lib
{
	namespace Renderer
	{
		enum class BufferBit : uint8_t
		{
			COLOR_BUFFER_BIT = 1 << 0,
			DEPTH_BUFFER_BIT = 1 << 1
		};

		inline BufferBit operator|(BufferBit lhs, BufferBit rhs)
		{
			return static_cast<BufferBit>(std::to_underlying(lhs) | std::to_underlying(rhs));
		}

		inline BufferBit operator&(BufferBit lhs, BufferBit rhs)
		{
			return static_cast<BufferBit>(std::to_underlying(lhs) & std::to_underlying(rhs));
		}

		void clear(BufferBit mask);
		void clear_color(float red, float green, float blue, float alpha);

		void set_viewport(int x, int y, uint16_t width, uint16_t height);

		void render_triangles(int32_t first, size_t count);
	}
}