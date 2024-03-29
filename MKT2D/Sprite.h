#pragma once

#include <GL/glew.h>
#include <string>
#include "GLTexture.h"

namespace MKT2D {

	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string textureFilepath);
		void draw();

	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID;
		GLTexture _texture;
	};

}