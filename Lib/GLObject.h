#pragma once

#include <cstdint>

#include "Defines.h"

namespace Lib
{
	class GLObject
	{
	protected:
		GLObject() noexcept = default;
		GLObject(uint32_t id) noexcept : m_id(id) {}

		DELETE_CPY_MOV_OP(GLObject);

	public:
		virtual ~GLObject() = default;

	public:
		virtual void bind() const = 0;

	protected:
		uint32_t m_id{};
	};
}