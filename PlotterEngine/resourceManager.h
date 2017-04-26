#pragma once
#include "textureCache.h"
#include <string> 
namespace PlotterEngine {
	class resourceManager
	{
	public:
		static GLTexture getTexture(std::string texturePath);
	private:
		static textureCache _textureCache;
	};

}
