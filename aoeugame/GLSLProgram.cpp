#include "Errors.h"
#include "GLSLProgram.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) {
}


GLSLProgram::~GLSLProgram() {
}

GLuint GLSLProgram::compileShader(std::string& filepath, unsigned int shaderType) {	
	GLuint shaderID = glCreateShader(shaderType);
	if (!shaderID) {
		fatalError("Failed to create shader");
	}

	std::ifstream shaderFile(filepath);
	if (shaderFile.fail()) {		
		fatalError("Failed to open " + filepath);
	}
	std::string fileContents;
	std::string line;
	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}
	shaderFile.close();

	const char* contents = fileContents.c_str();
	glShaderSource(shaderID, 1, &contents, nullptr);

	glCompileShader(shaderID);
	GLint isCompiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(shaderID);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Shader " + filepath + " failed to complie");
	}
	
	return shaderID;
}

void GLSLProgram::complieShaders(std::string& vertexShaderFilepath,
								 std::string& fragmentShaderFilepath) {
	_programID = glCreateProgram();
	_vertexShaderID = compileShader(vertexShaderFilepath, GL_VERTEX_SHADER);
	_fragmentShaderID = compileShader(fragmentShaderFilepath, GL_FRAGMENT_SHADER);
}

void GLSLProgram::linkShaders() {
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		fatalError("Failed to link shaders");
	}

	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(_programID, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found in shader");
	}
	return location;
}


void GLSLProgram::use() {
	glUseProgram(_programID);
	for (int att = 0; att < _numAttributes; att++) {
		glEnableVertexAttribArray(att);
	}
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int att = 0; att < _numAttributes; att++) {
		glDisableVertexAttribArray(att);
	}
}