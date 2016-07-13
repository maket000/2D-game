#include "TextureCache.h"
#include "ImageLoader.h"

namespace MKT2D {

	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}


	GLTexture TextureCache::getTexture(std::string filepath) {

		auto mit = _textureMap.find(filepath);
		if (mit == _textureMap.end()) {
			GLTexture newTexture = ImageLoader::loadPNG(filepath);
			_textureMap.insert(make_pair(filepath, newTexture));

			return newTexture;
		}
		return mit->second;
	}

}