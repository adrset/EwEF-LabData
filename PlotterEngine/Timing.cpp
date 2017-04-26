#include "Timing.h"
#include <SDL/SDL.h>
namespace PlotterEngine {

	FpsLimiter::FpsLimiter() {
	}
	void FpsLimiter::init(float targetFPS) {
		setMaxFPS(targetFPS);
	}
	void FpsLimiter::begin() {
		_startTicks = SDL_GetTicks();
	}
	float FpsLimiter::end() {
		_calculateFPS();
		int frameTicks = SDL_GetTicks() - _startTicks;

		if (1000.0f / _maxFPS > frameTicks) {
			SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));
		}
		return _fps;
	}

	void FpsLimiter::setMaxFPS(float targetFPS) {
		_maxFPS = targetFPS;
	}

	void FpsLimiter::_calculateFPS() {
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;

		static int prevTicks = SDL_GetTicks();

		int currentTicks;

		currentTicks = SDL_GetTicks();

		_frameTime = (float)(currentTicks - prevTicks); // _frameTime should be an unsigned int, SDL_GetTicks() returns always an usnigned int!
		frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

		prevTicks = currentTicks;
		int count;
		currentFrame++;

		if (currentFrame < NUM_SAMPLES) {
			count = currentFrame;
		}
		else {
			count = NUM_SAMPLES;
		}
		float frameTimeAv = 0;
		for (int i = 0; i < count; i++) {
			frameTimeAv += frameTimes[i];
		}
		frameTimeAv /= count;

		if (frameTimeAv > 0) {
			_fps = 1000.0f / frameTimeAv;
		}
		else {
			_fps = 60.0f;
		}
	}


}