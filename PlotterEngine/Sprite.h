#pragma once
#include <GL/glew.h>
#include <string>
#include "glTexture.h"

namespace PlotterEngine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height, std::string texturePath);
		void draw();
	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vboID; // unsigned int (but guarranted 32bits)
		GLTexture _texture;

	};

}