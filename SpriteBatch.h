#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Vertex.h"

#include <vector>

namespace helix
{
	struct Glyph
	{
		GLuint texture{};
		float depth{};
		Vertex top_left{};
		Vertex bottom_left{};
		Vertex bottom_right{};
		Vertex top_right{};
	};

	class RenderBatchData
	{
	public:
		RenderBatchData(GLuint Offset, GLuint Num_vertices, GLuint Texture)
			: offset{ Offset }
			, num_vertices{ Num_vertices }
			, texture{ Texture }
		{
		}
		GLuint offset{};
		GLuint num_vertices{};
		GLuint texture{};
	};

	class SpriteBatch
	{
	public:
		enum class SortType
		{
			NONE,
			FRONT_TO_BACK,
			BACK_TO_FRONT,
			TEXTURE
		};
		SpriteBatch();
		~SpriteBatch();
		void Init();

		void Begin(SortType sort_type = SortType::TEXTURE);
		void End();

		void Draw(const glm::vec4 &destination_quad, const glm::vec4 &uv_quad, GLuint texture, float depth, const ColorRGBA8 &color);

		void RenderBatch();
	private:
		void CreateRenderBatch();
		void CreateVAO();
		void SortGlyphs();

		// for std::stable_sort
		static bool CompareFrontToBack(Glyph *a, Glyph *b);
		static bool CompareBackToFront(Glyph *a, Glyph *b);
		static bool CompareTexture(Glyph *a, Glyph *b);

		GLuint m_vbo{};
		GLuint m_vao{};

		SortType m_sort_type{};
		std::vector<Glyph*> m_glyphs{};
		std::vector<RenderBatchData> m_render_batch_data{};
	};
}
#endif

