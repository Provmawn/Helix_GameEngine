#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H
#include <fstream>
#include <glad/glad.h>
namespace helix
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void CompileShaders(const std::string &vertex_shader, const std::string &fragment_shader);
		void LinkShaders();
		GLint GetUniformLocation(const std::string &name);
		void Use();
		void StopUsing();
	private:
		void CompileShader(const std::string &file_path, GLuint id);
		GLuint m_programID{};
		GLuint m_vertexID{};
		GLuint m_fragmentID{};
	};
}
#endif

