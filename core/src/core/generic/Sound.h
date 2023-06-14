#pragma once
#include "_Core.h"
#include "utility.h"

#include <MINIAUDIO/miniaudio.h>

namespace core {

    class Sound
    {
    private:
        std::string currentSoundFile;
        ma_engine engine;
        ma_sound currentSound;

    public:
        Sound();
        ~Sound();
        static void DataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
        bool InitSound();
        bool SoundPlay(std::string soundFile);
        bool StopSound();
        void SetVolume(float volume);
        float GetVolume();
    };

}