#include <cstddef>
#include "Sprite.h"
#include "Vertex.h"


Sprite::Sprite() : _vboID(0) {
}


Sprite::~Sprite() {
	if (_vboID) {
		glDeleteBuffers(1, &_vboID);
	}
}


void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (!_vboID) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];
	
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;
	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;
	vertexData[2].position.x = x;
	vertexData[2].position.y = x;
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;
	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;
    vertexData[5].position.x = x + width;
	vertexData[5].position.y = x + height;

	for (int vert = 0; vert < 6; vert++) {
		vertexData[vert].colour.r = 255;
		vertexData[vert].colour.g = 0;
		vertexData[vert].colour.b = 255;
		vertexData[vert].colour.a = 255; 
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
						  (void *)offsetof(Vertex, position)); // position
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
						  (void *)offsetof(Vertex, colour)); // colour



	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}