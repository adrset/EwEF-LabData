#pragma once
#include "glTexture.h"
#include "picoPng.h"
#include <string>
namespace PlotterEngine {
	class imageLoader
	{
	public:
		static GLTexture loadPng(std::string filePath);
	};

}
