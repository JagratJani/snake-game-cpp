#include "ColorManager.h"

ColorManager::ColorManager() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ColorManager::SetColor(int color) {
    SetConsoleTextAttribute(consoleHandle, color);
}

void ColorManager::ResetColor() {
    SetConsoleTextAttribute(consoleHandle, 7); // Reset to default light gray
}