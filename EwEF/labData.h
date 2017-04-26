#pragma once
#include <vector>
#include "gnuplot.h"
#include "BOD.h"
#include "ELVISt.h"
#include "ELVISf.h"
#include "SCP.h"
class labData
{
public:
	static std::string directory;
	labData(int width, int height, std::string dir = "");
	~labData();
	void menu();
private:
	gnuplot m_plot;
	std::vector <BOD> m_bods;
	std::vector <SCP> m_scps;
	std::vector <ELVISt> m_elvisT;
	std::vector <ELVISf> m_elvisF;


};

