#ifndef GLTEXTURE_H
#define GLTEXTURE_H
#include <glad/glad.h>
namespace helix
{
	struct GLTexture
	{
		GLuint id{};
		int width{};
		int height{};
	};
}
#endif