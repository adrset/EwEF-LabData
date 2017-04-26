#pragma once
#include <vector>
//static class - we need only one IO manager
namespace PlotterEngine {
	class IO
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}
