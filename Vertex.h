#ifndef VERTEX_H
#define VERTEX_H
#include <glad/glad.h>
namespace helix
{
	struct Position
	{
		float x{};
		float y{};
	};

	struct ColorRGBA8
	{
		GLubyte r{};
		GLubyte g{};
		GLubyte b{};
		GLubyte a{};
		ColorRGBA8()
			: r{ 0 }, g{ 0 }, b{ 0 }, a{ 255 }
		{}
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A)
			: r{ R }, g{ G }, b{ B }, a{ A }
		{}
	};

	struct UV
	{
		float u{};
		float v{};
	};

	struct Vertex
	{
		Position position{};
		ColorRGBA8 color{};
		UV uv{};

		void SetPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}

		void SetColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
	};
}
#endif