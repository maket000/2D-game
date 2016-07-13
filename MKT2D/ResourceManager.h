#pragma once

#include <string>
#include "TextureCache.h"

namespace MKT2D {

	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string filepath);

	private:
		static TextureCache _textureCache;

	};

}
