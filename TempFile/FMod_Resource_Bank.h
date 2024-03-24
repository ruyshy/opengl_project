#pragma once

#ifndef FMOD_RESOURCE_BANK_H_
#define FMOD_RESOURCE_BANK_H_

enum LoadBankMethod
{
    LoadBank_File,
    LoadBank_Memory,
    LoadBank_MemoryPoint,
    LoadBank_Custom
};

class FMODResourceBank
{
public:
    static FMOD_RESULT F_CALLBACK customFileOpen(const char* name, unsigned int* filesize, void** handle, void* userdata);
    static FMOD_RESULT F_CALLBACK customFileClose(void* handle, void* userdata);
    static FMOD_RESULT F_CALLBACK customFileRead(void* handle, void* buffer, unsigned int sizebytes, unsigned int* bytesread, void* userdata);
    static FMOD_RESULT F_CALLBACK customFileSeek(void* handle, unsigned int pos, void* userdata);

    static FMOD_RESULT loadFile(const char* filename, char** memoryBase, char** memoryPtr, int* memoryLength);
    static FMOD_RESULT loadBank(FMOD::Studio::System* system, LoadBankMethod method, const char* filename, FMOD::Studio::Bank** bank);

    static const char* getLoadingStateString(FMOD_STUDIO_LOADING_STATE state, FMOD_RESULT loadResult);
    static const char* getHandleStateString(FMOD::Studio::Bank* bank);


    static FMOD_RESULT F_CALLBACK studioCallback(FMOD_STUDIO_SYSTEM* system, FMOD_STUDIO_SYSTEM_CALLBACK_TYPE type, void* commanddata, void* userdata);


};


#endif // !FMOD_RESOURCE_BANK_H_
