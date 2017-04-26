#pragma once
#include <vector>
#include "Misc.h"
class ELVISt
{
public:
	bool readElvisFile(std::string filePath);
	void printAll();
	void saveFile();
	std::string getFileNameString() const { return m_fileName; }
	ELVISt();
	~ELVISt();
private:
	std::string m_fileName = "";
	std::vector < double > m_chTimeA;
	std::vector < double > m_chTimeB;
	std::vector < double > m_chValueA;
	std::vector < double > m_chValueB;
};

