#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>
namespace helix
{
    TextureCache::TextureCache()
    {

    }

    TextureCache::~TextureCache()
    {

    }

    GLTexture TextureCache::GetTexture(const std::string &texture_path)
    {
        auto map_it{ m_texture_map.find(texture_path) };
        if (map_it == m_texture_map.end())
        {
            GLTexture texture{ ImageLoader::LoadPNG(texture_path) };
            m_texture_map.insert(std::make_pair(texture_path, texture));
            std::cout << "Loading texture: " << texture_path << "\n";
            return texture;
        }
        return map_it->second;
    }
}
