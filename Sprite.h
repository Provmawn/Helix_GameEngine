#ifndef SPRITE_H
#define SPRITE_H
#include <glad/glad.h>
#include "GLTexture.h"
#include <string>
namespace helix
{
	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(float x, float y, float width, float height);
		~Sprite();
		void Init(float x, float y, float width, float height, const std::string &texture_path);

		void Draw();

	private:
		float m_x{};
		float m_y{};
		float m_width{};
		float m_height{};
		GLuint m_vao{};
		GLuint m_vbo{};
		GLuint m_ebo{};
		GLTexture m_texture{};
	};
}
#endif

