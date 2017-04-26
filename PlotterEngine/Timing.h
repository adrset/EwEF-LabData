#pragma once
namespace PlotterEngine {

	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float targetFPS);
		void begin();
		void setMaxFPS(float targetFPS);
		float end();//return FPS
	private:
		float _maxFPS;
		float _fps;
		float _frameTime;

		unsigned int _startTicks;
		void _calculateFPS();
	};

}