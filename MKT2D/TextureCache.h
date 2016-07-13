#pragma once

#include <map>
#include "GLTexture.h"

namespace MKT2D {

	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		GLTexture getTexture(std::string filepath);

	private:
		std::map<std::string, GLTexture> _textureMap;
	};

}
