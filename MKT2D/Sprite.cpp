#include <cstddef>
#include "ResourceManager.h"
#include "Sprite.h"
#include "Vertex.h"

namespace MKT2D {

	Sprite::Sprite() : _vboID(0) {
	}


	Sprite::~Sprite() {
		if (_vboID) {
			glDeleteBuffers(1, &_vboID);
		}
	}


	void Sprite::init(float x, float y, float width, float height, std::string textureFilepath) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;

		_texture = ResourceManager::getTexture(textureFilepath);

		if (!_vboID) {
			glGenBuffers(1, &_vboID);
		}

		Vertex vertexData[6];

		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);
		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);
		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);
		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);
		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int vert = 0; vert < 6; vert++) {
			vertexData[0].setColour(255, 0, 255, 255);
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw() {
		glBindTexture(GL_TEXTURE_2D, _texture.id);


		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							  (void *)offsetof(Vertex, position)); // position
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
							  (void *)offsetof(Vertex, colour)); // colour
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
							  (void *)offsetof(Vertex, uv));



		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}