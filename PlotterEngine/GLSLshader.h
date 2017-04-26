#pragma once
#include <string>
#include <GL/glew.h>
#include "errors.h"
namespace PlotterEngine {
	class GLSLshader
	{
	public:
		GLSLshader();
		~GLSLshader();
		void compileShader(const std::string& filePath, GLuint id);
		void compileShaders(const std::string& vertPath, const std::string& fragPath);
		void linkShaders();
		void addAttribute(const std::string& attribName);
		void use();
		void unuse();
		GLint getUniformLocation(const std::string uniformName);
	private:
		GLuint _programID;
		int _numAttributes;
		GLuint _vertID;
		GLuint _fragID;

	};
}
