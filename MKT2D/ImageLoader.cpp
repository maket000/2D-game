#include "Errors.h"
#include "GLTexture.h"
#include "IOManager.h"
#include "ImageLoader.h"
#include "picoPNG.h"
#include <GL/glew.h>

namespace MKT2D {

	GLTexture ImageLoader::loadPNG(std::string filepath) {
		GLTexture texture = {};

		std::vector<unsigned char> out;
		unsigned long width;
		unsigned long height;
		std::vector<unsigned char> in;
		if (!IOManager::readFileToBuffer(filepath, in)) {
			fatalError("Failed to load PNG file to buffer");
		}

		int error = decodePNG(out, width, height, &(in[0]), in.size());
		if (error) {
			fatalError("decodePNG failed with error: " + std::to_string(error));
		}

		glGenTextures(1, &(texture.id));

		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
					 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		texture.width = width;
		texture.height = height;

		return texture;
	}
}