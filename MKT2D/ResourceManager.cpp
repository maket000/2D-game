#include "ResourceManager.h"

namespace MKT2D {

	TextureCache ResourceManager::_textureCache;

	GLTexture ResourceManager::getTexture(std::string filepath) {
		return _textureCache.getTexture(filepath);
	}

}