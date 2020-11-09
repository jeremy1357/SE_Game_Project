#include "SoundDelegate.h"
#include <iostream>
#include <SDL/SDL.h>
SoundDelegate::SoundDelegate()
{
}

SoundDelegate::~SoundDelegate()
{
	//Mix_Quit();

}

void SoundDelegate::init_sound_delegate(const std::string& soundPathway)
{
	m_soundPathway = soundPathway + "Resources\\Sound\\";
	int status = Mix_Init(MIX_INIT_OGG);
	std::cout << "SDL Mixer Bit mask: " << status << std::endl;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
	}
}

void SoundDelegate::load_audio(const std::string& name)
{
	auto it = std::find_if(m_audioFiles.begin(), m_audioFiles.end(),
		[name](const auto& mo) {return mo.second.name == name; });
	if (it == m_audioFiles.end()) {
		std::string soundPath = m_soundPathway + name;
		Mix_Chunk* sample = Mix_LoadWAV(soundPath.c_str());
		if (sample == NULL) {
			printf("Mix_LoadWAV: %s\n", Mix_GetError());
		}
		int prevKey = m_audioFiles.size();
		m_audioFiles.insert(std::pair<int, AudioFile>(prevKey, AudioFile(name, sample)));
	}
}

void SoundDelegate::play_effect(int key)
{
	const auto& res = m_audioFiles.find(key);
	if (res->second.audioData != NULL) {
		int channel = Mix_PlayChannel(-1, res->second.audioData, 0);
		if (channel != -1) {
			res->second.channel = channel;
		}
	}
	
}

void SoundDelegate::stop_effect(int key)
{
	const auto& res = m_audioFiles.find(key);
	if (res->second.audioData != NULL) {
		Mix_HaltChannel(res->second.channel);
	}
}

void SoundDelegate::play_music(int key)
{
	const auto& res = m_audioFiles.find(key);
	if (res->second.audioData != NULL) {
		int channel = Mix_PlayChannel(-1, res->second.audioData, -1);
		if (channel != -1) {
			res->second.channel = channel;
		}
	}
}

void SoundDelegate::stop_music(int key)
{
	const auto& res = m_audioFiles.find(key);
	if (res->second.audioData != NULL) {
		Mix_HaltChannel(res->second.channel);
	}
}

int SoundDelegate::get_key(const std::string& name)
{
	auto it = std::find_if(m_audioFiles.begin(), m_audioFiles.end(),
		[name](const auto& mo) {
		return mo.second.name == name; });
	if (it != m_audioFiles.end()) {
		return it->first;
	}
	return 0;
}

