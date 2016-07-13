#pragma once

#include <GL/glew.h>
#include <string>

namespace MKT2D {

	class GLSLProgram {
	public:
		GLSLProgram();
		~GLSLProgram();
		void GLSLProgram::complieShaders(std::string& vertexShaderFilePath,
										 std::string& fragmentShaderFilepath);
		void linkShaders();
		void GLSLProgram::addAttribute(std::string& attributeName);

		GLint getUniformLocation(const std::string& uniformName);

		void use();
		void unuse();

	private:
		GLuint compileShader(std::string& filepath, unsigned int shaderType);

		int _numAttributes;

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
	};

}