#include "pch.h"
#include "FMod_Resource_Bank.h"

FMOD_RESULT F_CALLBACK FMODResourceBank::customFileOpen(const char* name, unsigned int* filesize, void** handle, void* userdata)
{
#ifdef ENABLE_FILE_OPEN
    // We pass the filename into our callbacks via userdata in the custom info struct
    const char* filename = (const char*)userdata;
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        return FMOD_ERR_FILE_NOTFOUND;
    }
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length >= MAX_FILE_LENGTH)
    {
        fclose(file);
        return FMOD_ERR_FILE_BAD;
    }
    *filesize = (unsigned int)length;
    *handle = file;
    return FMOD_OK;
#else
    return FMOD_ERR_FILE_NOTFOUND;
#endif
}

FMOD_RESULT F_CALLBACK FMODResourceBank::customFileClose(void* handle, void* userdata)
{
#ifdef ENABLE_FILE_OPEN
    FILE* file = (FILE*)handle;
    fclose(file);
#endif
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK FMODResourceBank::customFileRead(void* handle, void* buffer, unsigned int sizebytes, unsigned int* bytesread, void* userdata)
{
    *bytesread = 0;
#ifdef ENABLE_FILE_OPEN
    FILE* file = (FILE*)handle;
    size_t read = fread(buffer, 1, sizebytes, file);
    *bytesread = (unsigned int)read;
    // If the request is larger than the bytes left in the file, then we must return EOF
    if (read < sizebytes)
    {
        return FMOD_ERR_FILE_EOF;
    }
#endif
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK FMODResourceBank::customFileSeek(void* handle, unsigned int pos, void* userdata)
{
#ifdef ENABLE_FILE_OPEN
    FILE* file = (FILE*)handle;
    fseek(file, pos, SEEK_SET);
#endif
    return FMOD_OK;
}

FMOD_RESULT FMODResourceBank::loadFile(const char* filename, char** memoryBase, char** memoryPtr, int* memoryLength)
{
    // If we don't support fopen then just return a single invalid byte for our file
    size_t length = 1;

#ifdef ENABLE_FILE_OPEN
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        return FMOD_ERR_FILE_NOTFOUND;
    }
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (length >= MAX_FILE_LENGTH)
    {
        fclose(file);
        return FMOD_ERR_FILE_BAD;
    }
#endif

    // Load into a pointer aligned to FMOD_STUDIO_LOAD_MEMORY_ALIGNMENT
    char* membase = reinterpret_cast<char*>(malloc(length + FMOD_STUDIO_LOAD_MEMORY_ALIGNMENT));
    char* memptr = (char*)(((size_t)membase + (FMOD_STUDIO_LOAD_MEMORY_ALIGNMENT - 1)) & ~(FMOD_STUDIO_LOAD_MEMORY_ALIGNMENT - 1));

#ifdef ENABLE_FILE_OPEN
    size_t bytesRead = fread(memptr, 1, length, file);
    fclose(file);
    if (bytesRead != length)
    {
        free(membase);
        return FMOD_ERR_FILE_BAD;
    }
#endif

    * memoryBase = membase;
    *memoryPtr = memptr;
    *memoryLength = (int)length;
    return FMOD_OK;
}

FMOD_RESULT FMODResourceBank::loadBank(FMOD::Studio::System* system, LoadBankMethod method, const char* filename, FMOD::Studio::Bank** bank)
{
    if (method == LoadBank_File)
    {
        return system->loadBankFile(filename, FMOD_STUDIO_LOAD_BANK_NONBLOCKING, bank);
    }
    else if (method == LoadBank_Memory || method == LoadBank_MemoryPoint)
    {
        char* memoryBase;
        char* memoryPtr;
        int memoryLength;
        FMOD_RESULT result = loadFile(filename, &memoryBase, &memoryPtr, &memoryLength);
        if (result != FMOD_OK)
        {
            return result;
        }

        FMOD_STUDIO_LOAD_MEMORY_MODE memoryMode = (method == LoadBank_MemoryPoint ? FMOD_STUDIO_LOAD_MEMORY_POINT : FMOD_STUDIO_LOAD_MEMORY);
        result = system->loadBankMemory(memoryPtr, memoryLength, memoryMode, FMOD_STUDIO_LOAD_BANK_NONBLOCKING, bank);
        if (result != FMOD_OK)
        {
            free(memoryBase);
            return result;
        }

        if (method == LoadBank_MemoryPoint)
        {
            // Keep memory around until bank unload completes
            result = (*bank)->setUserData(memoryBase);
        }
        else
        {
            // Don't need memory any more
            free(memoryBase);
        }
        return result;
    }
    else
    {
        // Set up custom callback
        FMOD_STUDIO_BANK_INFO info;
        memset(&info, 0, sizeof(info));
        info.size = sizeof(info);
        info.opencallback = customFileOpen;
        info.closecallback = customFileClose;
        info.readcallback = customFileRead;
        info.seekcallback = customFileSeek;
        info.userdata = (void*)filename;

        return system->loadBankCustom(&info, FMOD_STUDIO_LOAD_BANK_NONBLOCKING, bank);
    }
}

const char* FMODResourceBank::getLoadingStateString(FMOD_STUDIO_LOADING_STATE state, FMOD_RESULT loadResult)
{
    switch (state)
    {
    case FMOD_STUDIO_LOADING_STATE_UNLOADING:
        return "unloading  ";
    case FMOD_STUDIO_LOADING_STATE_UNLOADED:
        return "unloaded   ";
    case FMOD_STUDIO_LOADING_STATE_LOADING:
        return "loading    ";
    case FMOD_STUDIO_LOADING_STATE_LOADED:
        return "loaded     ";
    case FMOD_STUDIO_LOADING_STATE_ERROR:
        // Show some common errors
        if (loadResult == FMOD_ERR_NOTREADY)
        {
            return "error (rdy)";
        }
        else if (loadResult == FMOD_ERR_FILE_BAD)
        {
            return "error (bad)";
        }
        else if (loadResult == FMOD_ERR_FILE_NOTFOUND)
        {
            return "error (mis)";
        }
        else
        {
            return "error      ";
        }
    default:
        return "???";
    };
}

const char* FMODResourceBank::getHandleStateString(FMOD::Studio::Bank* bank)
{
    if (bank == NULL)
    {
        return "null   ";
    }
    else if (!bank->isValid())
    {
        return "invalid";
    }
    else
    {
        return "valid  ";
    }
}

FMOD_RESULT F_CALLBACK FMODResourceBank::studioCallback(FMOD_STUDIO_SYSTEM* system, FMOD_STUDIO_SYSTEM_CALLBACK_TYPE type, void* commanddata, void* userdata)
{
    if (type == FMOD_STUDIO_SYSTEM_CALLBACK_BANK_UNLOAD)
    {
        // For memory-point, it is now safe to free our memory
        FMOD::Studio::Bank* bank = (FMOD::Studio::Bank*)commanddata;
        void* memory = nullptr;
        bank->getUserData(&memory);
        if (memory)
        {
            free(memory);
        }
    }
    return FMOD_OK;
}

