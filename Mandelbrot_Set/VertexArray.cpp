#include "VertexArray.h"

#include <glad/glad.h>

namespace Lib
{
	VertexArray::VertexArray() noexcept
	{
		glCreateVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		if (m_id) glDeleteVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}
}