#pragma once

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

using namespace FMOD;

enum class sound_type : unsigned int
{
	wav = 0,
	mp3,
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void InsertSound(const char* file_path, string audio_name);
	void InsertSound(UINT ID, string audio_name, sound_type type = sound_type::wav);
	void InsertStringSound(string music_string, string audio_name);

	FMOD::Sound* GetSound(string audio_name) { return mpSoundMap[audio_name]; }
	void ClearSound();

	unsigned int GetLength(string audio_name, FMOD_TIMEUNIT time_type = FMOD_TIMEUNIT_MS);
	void GetLength(string audio_name, unsigned int* time_length, FMOD_TIMEUNIT time_type = FMOD_TIMEUNIT_MS);

	System* GetSystem() { return mpSystem; }

	void playSound(string audio_name);
	void SystemUpdate();

private:
	map<string, FMOD::Sound*> mpSoundMap = map<string, FMOD::Sound*>();

private:
	System* mpSystem		=	nullptr;
	Channel* mpChannel	=	nullptr;
	FMOD_RESULT result	= FMOD_OK;

	unsigned int fmod_version	=	0;
	void* extradriverdata	=	nullptr;
	int state = 0;

};


#endif // !SOUNDMANAGER_H_
