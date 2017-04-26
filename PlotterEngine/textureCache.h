#pragma once
#include <map>
#include "glTexture.h"
namespace PlotterEngine {
	class textureCache
	{
	public:
		textureCache();
		~textureCache();
		GLTexture getTexture(std::string texturePath);
	private:
		std::map<std::string, GLTexture> _textureMap;
	};

}