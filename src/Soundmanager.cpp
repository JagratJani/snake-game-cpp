#include "SoundManager.h"

SoundManager::SoundManager() {
}

void SoundManager::PlayEatSound() const {
    // Single, smooth eating sound
    Beep(1000, 120); // Single medium-high pitch beep
}