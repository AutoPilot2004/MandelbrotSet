#include "ShaderProgram.h"

#include <string>
#include <fstream>

#include <glad/glad.h>

#include "Core.h"

static GLuint create_shader(GLenum type, const char* filePath)
{
	GLuint so = glCreateShader(type);

	std::ifstream file(filePath);
	if (!file) {
		return 0;
	}

	std::string conts;
	std::string curLine;

	while (std::getline(file, curLine)) {
		conts += curLine + '\n';
	}

	const char* ptr = conts.c_str();

	glShaderSource(so, 1, &ptr, nullptr);
	glCompileShader(so);

	return so;
}

static GLuint create_program(const char* vertPath, const char* fragPath)
{
	GLuint vso = create_shader(GL_VERTEX_SHADER, vertPath);
	if (!vso) return 0;
	GLuint fso = create_shader(GL_FRAGMENT_SHADER, fragPath);
	if (!fso) return 0;

	GLuint program = glCreateProgram();
	glAttachShader(program, vso);
	glAttachShader(program, fso);
	glLinkProgram(program);

	glDeleteShader(vso);
	glDeleteShader(fso);

	return program;
}

namespace Lib
{
	ShaderProgram::ShaderProgram(GLuint id) noexcept
		: GLObject(id)
	{}

	ShaderProgram::~ShaderProgram()
	{
		if (m_id) glDeleteProgram(m_id);
	}

	std::expected<ShaderProgram, ShaderProgram::Error> ShaderProgram::create(const char* vertPath, const char* fragPath) noexcept
	{
		GLuint programId = create_program(vertPath, fragPath);

		if (programId == 0) return std::unexpected(Error::CREATION_FAILED);

		return expected_from_invocable<ShaderProgram, Error>([=]() {
			return ShaderProgram(programId);
			});
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(m_id);
	}

	void ShaderProgram::uniform1i(int32_t location, int32_t value) const
	{
		glProgramUniform1i(m_id, location, value);
	}

	void ShaderProgram::uniform1d(int32_t location, double value) const
	{
		glProgramUniform1d(m_id, location, value);
	}

	void ShaderProgram::uniform2i(int32_t location, int32_t value1, int32_t value2) const
	{
		glProgramUniform2i(m_id, location, value1, value2);
	}

	void ShaderProgram::uniform2d(int32_t location, double value1, double value2) const
	{
		glProgramUniform2d(m_id, location, value1, value2);
	}
}