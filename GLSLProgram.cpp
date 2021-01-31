#include "GLSLProgram.h"
#include "Exception.h"
#include <iostream>
#include <sstream>
#include <vector>
namespace helix
{
	GLSLProgram::GLSLProgram()
		: m_programID{ 0 }
		, m_vertexID{ 0 }
		, m_fragmentID{ 0 }
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::CompileShaders(const std::string & vertex_shader, const std::string & fragment_shader)
	{
		try {
			m_vertexID = glCreateShader(GL_VERTEX_SHADER);
			if (m_vertexID == 0)
				throw Exception("Vertex Shader creation failure\n");
			m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
			if (m_fragmentID == 0)
				throw Exception("Fragment Shader creation failure\n");

			CompileShader(vertex_shader, m_vertexID);
			CompileShader(fragment_shader, m_fragmentID);

		}
		catch (const Exception &exception)
		{
			std::cerr << "Exception Occured(" << exception.what() << ")\n";
		}
		catch (const std::exception &exception)
		{
			std::cerr << "Other Exception has occured\n";
		}

	}

	void GLSLProgram::LinkShaders()
	{
		m_programID = glCreateProgram();

		glAttachShader(m_programID, m_vertexID);
		glAttachShader(m_programID, m_fragmentID);

		glLinkProgram(m_programID);

		try {
			GLint linked{};
			glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
			if (!linked)
			{
				GLint log_size{};
				glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &log_size);

				std::vector<char> error_log(log_size);
				glGetProgramInfoLog(m_programID, log_size, &log_size, &error_log[0]);

				glDeleteProgram(m_programID);
				glDeleteShader(m_vertexID);
				glDeleteShader(m_fragmentID);


				std::printf("%s\n", &(error_log[0]));
				throw Exception("Failed to link shaders\n");

				return;
			}
		}
		catch (const Exception &exception)
		{
			std::cerr << "Exception Occured(" << exception.what() << ")\n";
		}
		catch (const std::exception &exception)
		{
			std::cerr << "Other Exception Occured\n";
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_programID, m_vertexID);
		glDetachShader(m_programID, m_fragmentID);
		glDeleteShader(m_vertexID);
		glDeleteShader(m_fragmentID);
	}

	GLint GLSLProgram::GetUniformLocation(const std::string & name)
	{
		try {
			GLint location{ glGetUniformLocation(m_programID, name.c_str()) };
			if (location == GL_INVALID_INDEX)
				throw Exception("Uniform " + name + " not found in shader\n");
			return location;
		}
		catch (const Exception &exception)
		{
			std::cerr << "Exception Occured(" << exception.what() << ")\n";
		}
		catch (const std::exception &exception)
		{

			std::cerr << "Other Exception occured\n";
		}
	}

	void GLSLProgram::Use()
	{
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glUseProgram(m_programID);
	}

	void GLSLProgram::StopUsing()
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glUseProgram(0);
	}

	void GLSLProgram::CompileShader(const std::string & file_path, GLuint id)
	{
		std::stringstream shader_ss{};

		std::ifstream shader_stream{ file_path };
		if (!shader_stream)
			throw Exception("Shader " + file_path + " could not be opened\n");

		shader_ss << shader_stream.rdbuf();

		std::string shader_code_string{ shader_ss.str() };

		const char *shader_code{ shader_code_string.c_str() };

		glShaderSource(id, 1, &shader_code, nullptr);

		glCompileShader(id);

		try
		{
			GLint compiled{};
			glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
				GLint log_size{};
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size);
				std::vector<char> error_log(log_size);
				glGetShaderInfoLog(id, log_size, &log_size, &error_log[0]);

				glDeleteShader(id);

				std::printf("%s\n", &(error_log[0]));
				throw Exception("Shader " + file_path + " failed to compile\n");

				return;
			}
		}
		catch (const Exception &exception)
		{
			std::cerr << "Exception Occured(" << exception.what() << ")\n";
		}
		catch (const std::exception &exception)
		{
			std::cerr << "Other Exception Has Occured\n";
		}
	}
}
