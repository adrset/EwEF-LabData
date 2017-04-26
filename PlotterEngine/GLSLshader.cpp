#include "GLSLshader.h"
#include <fstream>
#include <vector>
namespace PlotterEngine {

	GLSLshader::GLSLshader() :_programID(0), _numAttributes(0), _vertID(0), _fragID(0)
	{
	}


	GLSLshader::~GLSLshader()
	{
	}

	GLint GLSLshader::getUniformLocation(const std::string uniformName) {
		GLint loc = glGetUniformLocation(_programID, uniformName.c_str());
		if (loc == GL_INVALID_INDEX)
			fatalError("Uniform " + uniformName + " not found in the shader");
		return loc;
	}
	void GLSLshader::compileShaders(const std::string& vertPath, const std::string& fragPath)
	{
		_programID = glCreateProgram();

		_vertID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertID == 0)
			fatalError("Could not create vert shader.");
		_fragID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragID == 0)
			fatalError("Could not create fragment shader.");
		compileShader(vertPath, _vertID);
		compileShader(fragPath, _fragID);

	}
	void GLSLshader::linkShaders()
	{

		glAttachShader(_programID, _vertID);
		glAttachShader(_programID, _fragID);

		glLinkProgram(_programID);

		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);

		if (isLinked == GL_FALSE) {
			GLint maxlength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxlength);

			std::vector<char> errorLog(maxlength);
			glGetProgramInfoLog(_programID, maxlength, &maxlength, &errorLog[0]);

			glDeleteProgram(_programID);

			glDeleteShader(_vertID);
			glDeleteShader(_fragID);//|^}
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link.");

		}

		glDetachShader(_programID, _vertID);
		glDetachShader(_programID, _fragID);

		glDeleteShader(_vertID);
		glDeleteShader(_fragID);//|^}
	}

	void GLSLshader::addAttribute(const std::string& attribName) {
		glBindAttribLocation(_programID, _numAttributes++, attribName.c_str());

	}

	void GLSLshader::use() {
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}
	void GLSLshader::unuse() {
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
			glDisableVertexAttribArray(i);
	}


	void GLSLshader::compileShader(const std::string& filePath, GLuint id) {
		std::ifstream vertFile(filePath);
		if (vertFile.fail()) {
			perror(filePath.c_str());
			fatalError("Failed to open " + filePath);
		}
		std::string fileContents = "";
		std::string line;
		while (std::getline(vertFile, line)) {
			fileContents += line + "\n";
		}

		vertFile.close();
		const char* contentsPtr = fileContents.c_str();
		glShaderSource(id, 1, &contentsPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (success = GL_FALSE) {
			GLint maxLength;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(id);
			std::printf("%s\n", &(errorLog[0]));
			fatalError("Shader " + filePath + " failed to compile.");

		}

	}

}