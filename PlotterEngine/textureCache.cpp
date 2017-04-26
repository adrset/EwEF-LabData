#include "textureCache.h"
#include "imageLoader.h"
#include <iostream>

namespace PlotterEngine {

	textureCache::textureCache()
	{
	}


	textureCache::~textureCache()
	{
	}

	GLTexture textureCache::getTexture(std::string texturePath) {

		//look for texture
		auto mit = _textureMap.find(texturePath);

		if (mit == _textureMap.end()) {
			GLTexture newTexture = imageLoader::loadPng(texturePath);
			_textureMap.insert(make_pair(texturePath, newTexture));
			//std::cout << "Loaded  texture!" << std::endl;
			return newTexture;
		}
		//std::cout << "Loaded cachced texture!" << std::endl;
		return mit->second;
	}

}