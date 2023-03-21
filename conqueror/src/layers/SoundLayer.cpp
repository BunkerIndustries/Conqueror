#include "_Game.h"
#include "SoundLayer.h"

void SoundLayer::OnAttach()
{
    soundSel.LoadSound("assets/sounds/menu.wav");
    soundTroll.LoadSound("assets/sounds/allahu_akbar.mp3");
}

void SoundLayer::OnDetach()
{

}

void SoundLayer::Update(const float dt)
{

}

void SoundLayer::Imgui(const float dt)
{
}

bool SoundLayer::OnKeyPressed(core::KeyPressedEvent& e)
{
    if (e.getKeyCode() == KEY_G && !e.getRepeated())
    {
        soundSel.PlaySound();
        volume = soundSel.GetVolume();
        return true;
    }

    if (e.getKeyCode() == KEY_Q && !e.getRepeated())
    {
        soundTroll.PlaySound();
        return true;
    }

    if (e.getKeyCode() == KEY_H && !e.getRepeated())
    {
        soundSel.StopSound();
        return true;
    }

    if (e.getKeyCode() == KEY_J && !e.getRepeated())
    {
        volume += 0.1f;
        soundSel.SetVolume(volume);
        return true;
    }

    if (e.getKeyCode() == KEY_K && !e.getRepeated())
    {
        volume -= 0.1f;
        soundSel.SetVolume(volume);
        return true;
    }
    return false;
}



