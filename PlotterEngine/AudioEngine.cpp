#include "AudioEngine.h"
#include "errors.h"
namespace PlotterEngine {


	AudioEngine::AudioEngine()
	{
		//empty
	}

	AudioEngine::~AudioEngine()
	{
		destroy(); // just to be sure
	}


	void AudioEngine::changeVolume(bool up) {
		std::cout << _volume << std::endl;
		if (up && _volume < 128) {
			Mix_Volume(-1, ++_volume);
			Mix_VolumeMusic(_volume);
		}
		else if(_volume > 0) {
			Mix_Volume(-1, --_volume);
			Mix_VolumeMusic(_volume);
		}
			
	}
	void AudioEngine::init()
	{
		if (m_isInitialised) {
			fatalError("Audio engine already initialised!");
		}
		//flags fac,mod,mp3,ogg
		if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1) {
		
			fatalError("Mix_Init error: " + std::string(Mix_GetError()));
		}
	
		if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1){

			fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
		}
		m_isInitialised = true;

		Mix_Volume(-1, _volume);
		Mix_VolumeMusic(_volume);
	}

	void AudioEngine::destroy()
	{
		if (m_isInitialised) {
			m_isInitialised = false;

			for(auto& it : m_effectMap) {//foreach
				Mix_FreeChunk(it.second);
			}
			for (auto& it : m_musicMap) {//foreach
				Mix_FreeMusic(it.second);
			}
			Mix_CloseAudio();
			Mix_Quit();
		}
	}

	SoundEffect AudioEngine::loadSoundEffect(const std::string& filePath)
	{

		//find in the cache
		auto it = m_effectMap.find(filePath);
		SoundEffect effect;
		if (it == m_effectMap.end()) {

			Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
			if (chunk == nullptr) {
				fatalError("Could not find the file!");
			}
			effect.m_chunk = chunk;
			m_effectMap[filePath] = chunk;
		}
		else {
			effect.m_chunk = it->second;
		}
		return effect;
	}

	Music AudioEngine::loadMusic(const std::string& filePath)
	{
		//find in the cache
		auto it = m_musicMap.find(filePath);
		Music music;
		if (it == m_musicMap.end()) {

			Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
			if (mixMusic == nullptr) {
				fatalError("Could not find the file!");
			}
			music.m_music = mixMusic;
			m_musicMap[filePath] = mixMusic;
		}
		else {
			music.m_music = it->second;
		}
		return music;
	}

	void SoundEffect::play(int loops)
	{
		if (Mix_PlayChannel(-1, m_chunk, loops) == -1) {//3 - loop function returns channel no.
			if (Mix_PlayChannel(0, m_chunk, loops) == -1) {
				fatalError("Could not play the effect: " + std::string(Mix_GetError()));
			}
		}
	}

	void Music::play(int loops)
	{
		if (Mix_PlayMusic(m_music, loops) == -1) {//3 - loop function returns channel no.
			fatalError("Could not play the music: " + std::string(Mix_GetError()));
		}
	}

	void Music::pause()
	{
		Mix_PausedMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}

}