#include "ResourceManager.h"

namespace helix
{
    TextureCache ResourceManager::texture_cache;

    GLTexture ResourceManager::GetTexture(const std::string & texture_path)
    {
        return texture_cache.GetTexture(texture_path);
    }
}
