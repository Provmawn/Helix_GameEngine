#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H
#include <string>
#include "GLTexture.h"
namespace helix
{
	class ImageLoader
	{
	public:
		static GLTexture LoadPNG(const std::string &file_path);
	};
}
#endif