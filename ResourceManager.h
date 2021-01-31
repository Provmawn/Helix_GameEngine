#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "TextureCache.h"
namespace helix
{
	class ResourceManager
	{
	public:
		static GLTexture GetTexture(const std::string &texture_path);

	private:
		static TextureCache texture_cache;
	};
}
#endif

