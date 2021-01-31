#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>
namespace helix
{
	Sprite::Sprite(float x, float y, float width, float height)
		: m_x{ x }
		, m_y{ y }
		, m_width{ width }
		, m_height{ height }
		, m_vao{ 0 }
		, m_vbo{ 0 }
		, m_ebo{ 0 }
	{
	}

	Sprite::~Sprite()
	{
		if (m_vao)
			glDeleteVertexArrays(1, &m_vao);
		if (m_vbo)
			glDeleteBuffers(1, &m_vbo);
		if (m_ebo)
			glDeleteBuffers(1, &m_ebo);
	}

	void Sprite::Init(float x, float y, float width, float height, const std::string &texture_path)
	{
		m_x = x;
		m_y = x;
		m_width = x;
		m_height = x;
		m_texture = ResourceManager::GetTexture(texture_path);

		Vertex vertices[4]{};
		vertices[0].SetPosition(x, y);
		vertices[0].SetUV(0.0f, 0.0f);
		vertices[1].SetPosition(x + width, y);
		vertices[1].SetUV(1.0f, 0.0f);
		vertices[2].SetPosition(x + width, y + height);
		vertices[2].SetUV(1.0f, 1.0f);
		vertices[3].SetPosition(x, y + height);
		vertices[3].SetUV(0.0f, 1.0f);

		for (int i{ 0 }; i < 4; ++i)
		{
			vertices[i].SetColor(255, 0, 255, 255);
		}

		vertices[1].SetColor(0, 0, 255, 255);
		vertices[3].SetColor(0, 255, 0, 255);




		unsigned int indices[]{
			0, 1, 2,
			0, 2, 3
		};

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);

		glBindVertexArray(m_vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


		// position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		// uv
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Sprite::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, m_texture.id);
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

