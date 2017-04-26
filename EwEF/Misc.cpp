#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "Misc.h"



std::string getFileName(std::string filePath)
{
	std::replace(filePath.begin(), filePath.end(), '\\', '/');
	
	std::istringstream iss(filePath);
	std::string token;
	while (std::getline(iss, token, '/'))
	{
		filePath = token;
	}
	return "\\" + filePath;
}

