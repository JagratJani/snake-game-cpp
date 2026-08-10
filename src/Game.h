#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"
#include "HighScore.h"
#include "SoundManager.h"
#include "ColorManager.h"
#include <vector>
#include <utility>

class Game {
private:
    static const int WIDTH = 30;
    static const int HEIGHT = 20;
    
    Snake snake;
    Snake snake2;
    Food food;
    HighScore highScore;
    SoundManager soundManager;
    ColorManager colorManager;
    std::vector<std::pair<int, int>> obstacles;
    int score;
    int score2;
    bool gameOver;
    bool paused;
    int loserPlayer;
    
    // Track food count for special food spawning
    int foodCount;
    
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
    void GenerateObstacles();
    
public:
    Game();
    void Run();
};

#endif