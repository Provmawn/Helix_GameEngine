#include "SpriteBatch.h"

#include <algorithm>

helix::SpriteBatch::SpriteBatch()
{
}

helix::SpriteBatch::~SpriteBatch()
{
}

void helix::SpriteBatch::Init()
{
	CreateVAO();
}

void helix::SpriteBatch::Begin(SpriteBatch::SortType sort_type)
{
	m_sort_type = sort_type;
	m_render_batch_data.clear();
	for (auto glyph : m_glyphs)
		delete glyph;
	m_glyphs.clear();
}

void helix::SpriteBatch::End()
{
	SortGlyphs();
	CreateRenderBatch();
}

void helix::SpriteBatch::Draw(const glm::vec4 & destination_quad, const glm::vec4 & uv_quad, GLuint texture, float depth, const ColorRGBA8 & color)
{
	Glyph *glyph{ new Glyph };
	glyph->texture = texture;
	glyph->depth = depth;
	glyph->top_left.SetColor(color.r, color.g, color.b, color.a);
	glyph->top_left.SetPosition(destination_quad.x, destination_quad.y + destination_quad.w);
	glyph->top_left.SetUV(uv_quad.x, uv_quad.y + uv_quad.w);

	glyph->bottom_left.SetColor(color.r, color.g, color.b, color.a);
	glyph->bottom_left.SetPosition(destination_quad.x, destination_quad.y);
	glyph->bottom_left.SetUV(uv_quad.x, uv_quad.y);

	glyph->bottom_right.SetColor(color.r, color.g, color.b, color.a);
	glyph->bottom_right.SetPosition(destination_quad.x + destination_quad.z, destination_quad.y);
	glyph->bottom_right.SetUV(uv_quad.x + uv_quad.z, uv_quad.y);
	
	glyph->top_right.SetColor(color.r, color.g, color.b, color.a);
	glyph->top_right.SetPosition(destination_quad.x + destination_quad.z, destination_quad.y + destination_quad.w);
	glyph->top_right.SetUV(uv_quad.x + uv_quad.z, uv_quad.y + uv_quad.w);


	m_glyphs.push_back(glyph);
}

void helix::SpriteBatch::RenderBatch()
{
	glBindVertexArray(m_vao);
	for (auto &batch : m_render_batch_data)
	{
		glBindTexture(GL_TEXTURE_2D, batch.texture);
		glDrawArrays(GL_TRIANGLES, batch.offset, batch.num_vertices);
	}
	glBindVertexArray(0);
}

void helix::SpriteBatch::CreateRenderBatch()
{
	if (m_glyphs.empty())
		return;

	std::vector<Vertex> vertices{};
	vertices.resize(m_glyphs.size() * 6);

	int offset{ 0 };
	int current_vertex{ 0 };


	m_render_batch_data.emplace_back(offset, 6, m_glyphs[0]->texture);
	vertices[current_vertex++] = m_glyphs[0]->top_left;
	vertices[current_vertex++] = m_glyphs[0]->bottom_left;
	vertices[current_vertex++] = m_glyphs[0]->bottom_right;
	vertices[current_vertex++] = m_glyphs[0]->bottom_right;
	vertices[current_vertex++] = m_glyphs[0]->top_right;
	vertices[current_vertex++] = m_glyphs[0]->top_left;
	offset = current_vertex;

	for (int current{ 1 }; current < m_glyphs.size(); ++current)
	{
		if (m_glyphs[current]->texture != m_glyphs[current - 1]->texture)
			m_render_batch_data.emplace_back(offset, 6, m_glyphs[current]->texture);
		else
			m_render_batch_data.back().num_vertices += 6;

		vertices[current_vertex++] = m_glyphs[current]->top_left;
		vertices[current_vertex++] = m_glyphs[current]->bottom_left;
		vertices[current_vertex++] = m_glyphs[current]->bottom_right;
		vertices[current_vertex++] = m_glyphs[current]->bottom_right;
		vertices[current_vertex++] = m_glyphs[current]->top_right;
		vertices[current_vertex++] = m_glyphs[current]->top_left;
		offset = current_vertex;
	}
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void helix::SpriteBatch::CreateVAO()
{
	if (m_vao == 0)
		glGenVertexArrays(1, &m_vao);
	if (m_vbo == 0)
		glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

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
}

void helix::SpriteBatch::SortGlyphs()
{
	switch (m_sort_type)
	{
	case SortType::BACK_TO_FRONT:
		std::stable_sort(m_glyphs.begin(), m_glyphs.end(), CompareBackToFront);
		break;
	case SortType::FRONT_TO_BACK:
		std::stable_sort(m_glyphs.begin(), m_glyphs.end(), CompareFrontToBack);
		break;
	case SortType::TEXTURE:
		std::stable_sort(m_glyphs.begin(), m_glyphs.end(), CompareTexture);
		break;
	}
}

bool helix::SpriteBatch::CompareFrontToBack(Glyph * a, Glyph * b)
{
	return (a->depth < b->depth);
}

bool helix::SpriteBatch::CompareBackToFront(Glyph * a, Glyph * b)
{
	return (a->depth > b->depth);
}

bool helix::SpriteBatch::CompareTexture(Glyph * a, Glyph * b)
{
	return (a->texture < b->texture);
}
