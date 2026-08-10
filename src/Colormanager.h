#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include <windows.h>

class ColorManager {
private:
    HANDLE consoleHandle;
    
public:
    ColorManager();
    void SetColor(int color);
    void ResetColor();
    
    // Color constants
    static const int SNAKE_HEAD = 11;    // Bright Cyan
    static const int SNAKE_BODY = 2;     // Green
    static const int FOOD = 12;          // Bright Red
    static const int WALL = 15;          // Bright White
    static const int SCORE = 15;         // Bright White
    static const int MENU_TITLE = 14;    // Bright Yellow
    static const int MENU_SELECTED = 11; // Bright Cyan
    static const int MENU_NORMAL = 7;    // Light Gray
    static const int GAME_OVER = 12;     // Bright Red
    static const int HIGH_SCORE = 10;    // Bright Green
    static const int OBSTACLE = 8;       // Gray for obstacles
};

#endif