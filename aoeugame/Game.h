#pragma once


#include <MKT2D/GLSLProgram.h>
#include <MKT2D/Sprite.h>
#include <MKT2D/Window.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>

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
	void initShader(MKT2D::GLSLProgram& program, std::string vertFilepath, std::string fragFilepath,
					int attributeCount, std::string attributes[]);
	void initShaders();
	void initSys();

	void processInput();
	void drawGame();
	void calculateFPS();
	void gameLoop();

	MKT2D::Window _window;
	int _screenWidth;
	int _screenHeight;

	GameState _gameState;
	std::vector<MKT2D::Sprite*> _sprites;
	MKT2D::GLSLProgram _colorProgram;

	float _maxFPS;
	float _ticksPerFrame;
	float _FPS;
	int _frameCount;
	float _frameTime;
	int NUM_SAMPLES;
	float * _frameTimes;
	float _prevTicks;
};

