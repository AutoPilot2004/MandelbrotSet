#pragma once

#include <expected>

#include "GLObject.h"

namespace Lib
{
	class ShaderProgram : public GLObject
	{
	public:
		enum class Error
		{
			CREATION_FAILED
		};

	private:
		ShaderProgram(uint32_t id) noexcept;

	public:
		~ShaderProgram();

	public:
		static std::expected<ShaderProgram, Error> create(const char* vertPath, const char* fragPath) noexcept;

	public:
		void bind() const override;

		void uniform1i(int32_t location, int32_t value)                  const;
		void uniform1d(int32_t location, double value)                   const;
		void uniform2i(int32_t location, int32_t value1, int32_t value2) const;
		void uniform2d(int32_t location, double value1, double value2)   const;
	};
}