#include "Texture1D.h"

#include <glad/glad.h>

namespace Lib
{
	Texture1D::Texture1D(const void* data, std::uint16_t width) noexcept
	{
		glCreateTextures(GL_TEXTURE_1D, 1, &m_id);

		glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		bind();
		glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glTextureStorage1D(m_id, 0, GL_RGB, width);
		//glTextureSubImage1D(m_id, 0, 0, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(m_id);
	}

	Texture1D::~Texture1D()
	{
		if (m_id) glDeleteTextures(1, &m_id);
	}

	void Texture1D::bind() const
	{
		glBindTexture(GL_TEXTURE_1D, m_id);
	}

	void Texture1D::bind_unit(uint32_t unit) const
	{
		glBindTextureUnit(unit, m_id);
	}
}