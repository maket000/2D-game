#include <iostream>
#include <string>
#include "MKT2D/Errors.h"
#include "MKT2D/MKT2D.h"
#include "Game.h"


Game::Game() : _screenWidth(1024),
	           _screenHeight(720),
               _gameState(GameState::PLAY),
               _frameCount(1),
               NUM_SAMPLES(60),
               _prevTicks(0),
			   _maxFPS(60.0f) {
	_frameTimes = new float[NUM_SAMPLES];
	_ticksPerFrame = 1000.0f / _maxFPS;
}

Game::~Game() {
}

void Game::initShader(MKT2D::GLSLProgram& program, std::string vertFilepath, std::string fragFilepath,
					  int attributeCount, std::string attributes[]) {
	program.complieShaders(vertFilepath, fragFilepath);
	for (int att = 0; att < attributeCount; att++) {
		program.addAttribute(attributes[att]);
	}
	program.linkShaders();
}

void Game::initShaders() {
	int attributeCount = 3;
	std::string attributes[] = { "vertexPosition", "vertexColour", "vertexUV" };
	initShader(_colorProgram, "Shaders/colorShading.vert",
			   "Shaders/colorShading.frag", attributeCount, attributes);
}

void Game::initSys() {
	MKT2D::init();

	_window.create("aoeugame", _screenWidth, _screenHeight, MKT2D::WN_BORDERLESS);

	initShaders();
}

void Game::processInput() {
	SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				evnt.motion.x;
				evnt.motion.y;
				break;
		}
	}
}

void Game::drawGame() {
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);

	GLint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _frameCount);
	GLint textureLocation = _colorProgram.getUniformLocation("samplerTexture");
	glUniform1f(textureLocation, 0);

	for (int sprite = 0; sprite < _sprites.size(); sprite++) {
		_sprites[sprite]->draw();
	}

	_colorProgram.unuse();

	_window.swapBuffer();
}

void Game::calculateFPS() {
	float currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - _prevTicks;
	_frameTimes[_frameCount % NUM_SAMPLES] = _frameTime;

	_prevTicks = currentTicks;

	int count;

	if (_frameCount < NUM_SAMPLES) {
		count = _frameCount;
	} else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int t = 0; t < count; t++) {
		frameTimeAverage += _frameTimes[t];
	}
	frameTimeAverage /= count;

	_FPS = frameTimeAverage ? 1000.0f / frameTimeAverage : 60.0f;
}

void Game::gameLoop() {
	while (_gameState != GameState::EXIT) {
		float startTicks = SDL_GetTicks();
		processInput();
		drawGame();

		//calculateFPS();
		//std::cout << _fps << std::endl;
		_frameCount++;

		float frameTicks = SDL_GetTicks() - startTicks;
		if (frameTicks < _ticksPerFrame) {
			SDL_Delay(_ticksPerFrame - frameTicks);
		}
	}
}

void Game::run() {
	initSys();

	_sprites.push_back(&MKT2D::Sprite());
	_sprites.back()->init(-1, -1, 1, 1, "res/sprite_0000.png");
	_sprites.push_back(&MKT2D::Sprite());
	_sprites.back()->init(-1, 0, 1, 1, "res/sprite_0000.png");

	gameLoop();
}