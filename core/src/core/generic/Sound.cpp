#include "_Core.h"

#include "Sound.h"


namespace core {

    Sound::Sound()
    {
        // initialize the engine without specific configuration
        if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
        {
            LOG_CORE_ERROR("Failed to initialize the engine");
        }
    }

    Sound::~Sound()
    {
        StopSound();
        ma_sound_uninit(&currentSound);
        ma_engine_uninit(&engine);
    }

    void Sound::DataCallback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
    {
        // callback function, this is being called when playSound is issued, but as a background thread
        ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
        if (pDecoder == NULL)
        {
            LOG_CORE_ERROR("Failed to initialize the sound decoder");
            return;
        }
        ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

        (void)pInput;
    }

    bool Sound::LoadSound(std::string soundFile)
    {
        Sound::soundFile = soundFile;

        // use the high level api || we are using it because we are already including the library 
        // and we can make use of the high level functions in order to play sounds with their own group

        if (ma_sound_init_from_file(&engine, soundFile.c_str(), 0, NULL, NULL, &currentSound) != MA_SUCCESS)
        {
            LOG_CORE_ERROR("Failed to load sound '" + std::string(soundFile) + "'");
            return false;
        }

        SetVolume(0.6);
        return true;
    }

    bool Sound::SoundPlay()
    {
        // TODO: make the function add different sound ,,objects'' ma_sound sound = ma_sound_init_from_file ...
        // play sound and specify a sound group (different sound groups can be used to specify their volumes)

        if (ma_sound_start(&currentSound) != MA_SUCCESS)
        {
            LOG_CORE_ERROR("Could not play sound '" + std::string(soundFile) + "'");
            return false;
        }

        return true;
    }

    bool Sound::StopSound()
    {
        if (ma_sound_stop(&currentSound) != MA_SUCCESS)
        {
            LOG_CORE_ERROR("Could not stop sound '" + std::string(soundFile) + "'");
            return false;
        }
        return true;
    }

    void Sound::SetVolume(float volume)
    {
        ma_sound_set_volume(&currentSound, volume);
    }

    float Sound::GetVolume()
    {
        return ma_sound_get_volume(&currentSound);
    }

}