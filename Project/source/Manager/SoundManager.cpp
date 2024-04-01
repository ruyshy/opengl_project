#include <pch.h>
#include <Manager/SoundManager.h>

#include <Manager/ResourceManager.h>
#include <utill/string_converter.h>

#define reslut_check()											\
if (result != FMOD_OK) {	state = -1;	return;	}			\

#define reslut_return()											\
if (result != FMOD_OK) 	return;								\

SoundManager::SoundManager()
{
	result = FMOD::System_Create(&mpSystem);
	reslut_check();
	result = mpSystem->getVersion(&fmod_version);
	reslut_check();
	result = mpSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	reslut_check();

	//result = mpSystem->createSound(".\\sound\\note sound A.wav", FMOD_LOOP_OFF, 0, &sound);

	reslut_check();

	//result = mpSystem->playSound(sound, 0, false, &mpChannel);
	reslut_check();
}

SoundManager::~SoundManager()
{
	ClearSound();
	mpSystem->release();
}

void SoundManager::InsertSound(const char* file_path, string audio_name)
{
	Sound* sound;

	mpSystem->createSound(file_path, FMOD_LOOP_OFF, 0, &sound);
	mpSoundMap.insert(make_pair(audio_name, sound));
}

void SoundManager::InsertSound(UINT ID, string audio_name, sound_type type)
{
	DWORD audio_size;
	Sound* sound;
	Resource re = Resource::SOUND_WAV;
	switch (type)
	{
	case sound_type::wav:
		re = Resource::SOUND_WAV;
		break;
	case sound_type::mp3:
		re = Resource::SOUND_MP3;
		break;
	}
	const char* sound_const_char = static_cast<const char*>(ResourceManager::GetResourceLPVOID(ID,
		re, audio_size));
	FMOD_CREATESOUNDEXINFO AudioInfo;
	memset(&AudioInfo, 0, sizeof(FMOD_CREATESOUNDEXINFO));
	AudioInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	AudioInfo.length = static_cast<unsigned int>(audio_size);

	result = mpSystem->createSound(
		sound_const_char,
		FMOD_OPENMEMORY | FMOD_LOOP_OFF, &AudioInfo, &sound
	);

	reslut_return();

	mpSoundMap.insert(make_pair(audio_name, sound));
}

void SoundManager::InsertStringSound(string music_string, string audio_name)
{

}

void SoundManager::ClearSound()
{
	for (auto iter = mpSoundMap.begin(); iter != mpSoundMap.end();)
	{
		(iter)->second->release();
		mpSoundMap.erase(iter++);
	}
}

unsigned int SoundManager::GetLength(string audio_name, FMOD_TIMEUNIT time_type)
{
	unsigned int play_time = -1;
	mpSoundMap[audio_name]->getLength(&play_time, time_type);
	return play_time;
}

void SoundManager::GetLength(string audio_name, unsigned int* time_length, FMOD_TIMEUNIT time_type)
{
	mpSoundMap[audio_name]->getLength(time_length, time_type);
}

void SoundManager::playSound(string audio_name)
{
	result = mpSystem->playSound(mpSoundMap[audio_name], 0, false, &mpChannel);
	reslut_return();

}

void SoundManager::SystemUpdate()
{
	mpSystem->update();
}
