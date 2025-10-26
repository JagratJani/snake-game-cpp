#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include "HighScore.h"
#include "SoundManager.h"  // Add this line

class Game {
private:
    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    
    Snake snake;
    Food food;
    HighScore highScore;
    SoundManager soundManager;  // Add this line
    int score;
    bool gameOver;
    bool paused;
    
    void Draw();
    void Input();
    void Logic();
    void GameOverScreen();
    void EnterHighScore();
    void Reset();
    void PauseGame();
    void ShowMainMenu();
    void ShowHelpScreen();
    void DrawMenuBorder();
    void StartGame();
    
public:
    Game();
    void Run();
};

#endif