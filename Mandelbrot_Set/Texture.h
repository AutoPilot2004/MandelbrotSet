#pragma once

#include <cstdint>

#include "GLObject.h"

namespace Lib
{
	class Texture : public GLObject
	{
	public:
		Texture(const void* data, uint16_t width) noexcept;
		~Texture();

	public:
		void bind() const override;

		void bind_unit(uint32_t unit) const;
	};
}