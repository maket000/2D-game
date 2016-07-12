#include <iostream>
#include <string>
#include "Errors.h"
#include "Game.h"


Game::Game() : _window(nullptr), _screenWidth(1024), _screenHeight(720),
               _gameState(GameState::PLAY), _tick(0) {
}

Game::~Game() {
}

void Game::initShader(GLSLProgram& program, std::string vertFilepath, std::string fragFilepath,
					  int attributeCount, std::string attributes[]) {
	program.complieShaders(vertFilepath, fragFilepath);
	for (int att = 0; att < attributeCount; att++) {
		program.addAttribute(attributes[att]);
	}
	program.linkShaders();
}

void Game::initShaders() {
	std::string attributes[] = { "vertexPosition", "vertexColour" };
	initShader(_colorProgram, "Shaders/colorShading.vert",
			   "Shaders/colorShading.frag", 2, attributes);
}

void Game::initSys() {
	SDL_Init(SDL_INIT_EVERYTHING);

	_window = SDL_CreateWindow("aoeuGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (!_window) {
		fatalError("SDL window could not be created");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (!glContext) {
		fatalError("SDL_GL context could not be created");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew");
	}

	initShaders();

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(1.0f, 0, 1.0f, 1.0f);
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
	GLuint timeLocation = _colorProgram.getUniformLocation("time");
	glUniform1f(timeLocation, _tick);

	_sprite.draw();

	_colorProgram.unuse();


	SDL_GL_SwapWindow(_window);
}

void Game::gameLoop() {
	while (_gameState != GameState::EXIT) {
		processInput();
		drawGame();
		_tick += 0.01f;
	}
}

void Game::run() {
	initSys();
	_sprite.init(-1, -1, 2, 2);

	gameLoop();
}
