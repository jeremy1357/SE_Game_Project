#pragma once
#include <string>
#include <map>
#include <SDL/SDL_mixer.h>


struct AudioFile {
	AudioFile(const std::string& name, Mix_Chunk* audioData) {
		this->name = name;
		this->audioData = audioData;
	}
	std::string name;
	Mix_Chunk* audioData;
};
class SoundDelegate
{
public:
	SoundDelegate();
	~SoundDelegate();
	void init_sound_delegate(const std::string& soundPathway);
	void load_WAV(const std::string& name);
	void play_effect(int key);
	void stop_effect();
private:
	std::string m_soundPathway;
	std::map <int, AudioFile> m_audioFiles;
};

