#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <windows.h>

class SoundManager {
public:
    SoundManager();
    void PlayEatSound() const;
    void PlayMenuSelectSound() const;
};

#endif