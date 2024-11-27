#pragma once

#include <cstdint>

#include "GLObject.h"

namespace Lib
{
	class Texture1D : public GLObject
	{
	public:
		Texture1D(const void* data, uint16_t width) noexcept;
		~Texture1D();

	public:
		void bind() const override;

		void bind_unit(uint32_t unit) const;
	};
}