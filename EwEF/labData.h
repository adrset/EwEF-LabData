#pragma once
#include <vector>
#include <PlotterEngine/PlotterEngine.h>
#include <PlotterEngine/window.h>
#include <PlotterEngine/InputManager.h>
#include <PlotterEngine/camera2d.h>
#include <PlotterEngine/SpriteFont.h>
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
	void initPlotter();
	void menu();
private:
	gnuplot m_plot;
	PlotterEngine::window m_window;
	std::vector <BOD> m_bods;
	std::vector <SCP> m_scps;
	std::vector <ELVISt> m_elvisT;
	std::vector <ELVISf> m_elvisF;

	PlotterEngine::InputManager m_inputManager; ///< Handles input
	PlotterEngine::camera2d m_camera; ///< Main Camera
	PlotterEngine::camera2d m_hudCamera; ///< Hud Camera
	PlotterEngine::SpriteFont* m_spriteFont;

	int m_screenWidth = 1024;
	int m_screenHeight = 768;

};

