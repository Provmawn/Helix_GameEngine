#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H
#include <map>
#include <string>

#include "GLTexture.h"
namespace helix
{
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture GetTexture(const std::string &texture_path);
	private:
		std::map<std::string, GLTexture> m_texture_map{};
	};
}
#endif

