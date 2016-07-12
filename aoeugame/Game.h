#pragma once

#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GLSLProgram.h"
#include "Sprite.h"

enum class GameState {
	PLAY,
	EXIT
};

class Game
{
public:
	Game();
    ~Game();

	void run();

private:
	void initShader(GLSLProgram& program, std::string vertFilepath, std::string fragFilepath,
					int attributeCount, std::string attributes[]);
	void initShaders();
	void initSys();

	void processInput();
	void drawGame();
	void gameLoop();

	SDL_Window *_window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;
	float _tick;
	Sprite _sprite;
	GLSLProgram _colorProgram;
};

