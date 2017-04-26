#include "resourceManager.h"

namespace PlotterEngine {
	textureCache resourceManager::_textureCache;

	GLTexture resourceManager::getTexture(std::string texturePath) {
		return _textureCache.getTexture(texturePath);

	}
}