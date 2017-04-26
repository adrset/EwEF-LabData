#pragma once
#include <SDL/SDL_mixer.h>
#include <string>
#include <map>
namespace PlotterEngine {

	class SoundEffect {
	public:
		friend class AudioEngine;
		//-1 loop forever
		void play(int loops = 0);
	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	class Music {
	public:
		friend class AudioEngine;
		void play(int loops = 1);
		static void pause();
		static void stop();
		static void resume();
	private:
		Mix_Music* m_music = nullptr;
	};

	class AudioEngine{
	public:
		AudioEngine();
		~AudioEngine();
		
		void changeVolume(bool up);
		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);
	private: 
		bool m_isInitialised = false;
		int _volume = 64;
		std::map<std::string, Mix_Music*> m_musicMap;
		std::map<std::string, Mix_Chunk*> m_effectMap;
	};

}