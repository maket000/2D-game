#pragma once

#include <string>
#include "GLTexture.h"

namespace MKT2D {

	static class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filepath);
	};

}