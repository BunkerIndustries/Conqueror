#include "SoundLayer.h"

void SoundLayer::OnAttach()
{
    soundSel.loadSound("assets/sounds/menu.wav");
    soundTroll.loadSound("assets/sounds/allahu_akbar.mp3");
}

void SoundLayer::OnDetach()
{

}

void SoundLayer::update(const float dt)
{

}

void SoundLayer::imgui(const float dt)
{
}

bool SoundLayer::OnKeyPressed(core::KeyPressedEvent& e)
{
    if (e.getKeyCode() == KEY_G && !e.getRepeated())
    {
        soundSel.playSound();
        volume = soundSel.getVolume();
    }

    if (e.getKeyCode() == KEY_Q && !e.getRepeated())
    {
        soundTroll.playSound();
    }

    if (e.getKeyCode() == KEY_H && !e.getRepeated())
    {
        soundSel.stopSound();
    }

    if (e.getKeyCode() == KEY_J && !e.getRepeated())
    {
        volume += 0.1f;
        soundSel.setVolume(volume);
    }

    if (e.getKeyCode() == KEY_K && !e.getRepeated())
    {
        volume -= 0.1f;
        soundSel.setVolume(volume);
    }
    return true;
}



