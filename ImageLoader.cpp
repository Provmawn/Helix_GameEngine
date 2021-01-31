#include "ImageLoader.h"
#include <SDL_image.h>

#include "Exception.h"
namespace helix
{
	GLTexture ImageLoader::LoadPNG(const std::string &file_path)
	{
		GLTexture texture{};
		SDL_Surface *image = IMG_Load(file_path.c_str());
		if (!image)
			throw Exception("Unable to load image: " + file_path + "\n");

		texture.width = image->w;
		texture.height = image->h;

		int mode{ GL_RGB };
		if (image->format->BytesPerPixel == 4)
			mode = GL_RGBA;

		glGenTextures(1, &(texture.id));
		glBindTexture(GL_TEXTURE_2D, texture.id);

		glTexImage2D(GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);


		glBindTexture(GL_TEXTURE_2D, 0);
		SDL_FreeSurface(image);
		return texture;

	}
}
