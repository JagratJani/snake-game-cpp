#include "SoundManager.h"

SoundManager::SoundManager() {
}

void SoundManager::PlayEatSound() const {
    Beep(800, 100);
}

void SoundManager::PlayMenuSelectSound() const {
    Beep(600, 80);
}