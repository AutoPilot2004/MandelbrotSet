#pragma once

#include "GLObject.h"

namespace Lib
{
	class VertexArray : public GLObject
	{
	public:
		VertexArray() noexcept;
		~VertexArray();

	public:
		void bind() const override;
	};
}
