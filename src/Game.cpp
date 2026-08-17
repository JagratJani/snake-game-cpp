#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>

using namespace std;

Game::Game() : food(WIDTH, HEIGHT), gameOver(false), paused(false), foodCount(0), losingPlayer(0) {
    snakes.push_back(Snake(WIDTH, HEIGHT, WIDTH / 2 - 4, HEIGHT / 2, RIGHT));
    snakes.push_back(Snake(WIDTH, HEIGHT, WIDTH / 2 + 4, HEIGHT / 2, LEFT));
    scores.push_back(0);
    scores.push_back(0);
    GenerateObstacles();
    food.GenerateWithObstacles(snakes, obstacles);
}

void Game::GenerateObstacles() {
    obstacles.clear();
    srand(static_cast<unsigned int>(time(nullptr)));
    int safeZoneX = WIDTH / 2;
    int safeZoneY = HEIGHT / 2;
    int safeRadius = 4;
    
    for (int i = 0; i < 3; i++) {
        int wallX = 5 + (rand() % (WIDTH - 10));
        int wallY = 3 + (rand() % (HEIGHT - 6));
        int wallHeight = 3 + (rand() % 4);
        if (abs(wallX - safeZoneX) < safeRadius) continue;
        for (int y = wallY; y < wallY + wallHeight && y < HEIGHT - 1; y++) {
            if (y > 1 && y < HEIGHT - 1 && abs(y - safeZoneY) >= safeRadius) {
                obstacles.push_back({wallX, y});
            }
        }
    }
    
    for (int i = 0; i < 3; i++) {
        int wallY = 5 + (rand() % (HEIGHT - 10));
        int wallX = 3 + (rand() % (WIDTH - 6));
        int wallWidth = 4 + (rand() % 5);
        if (abs(wallY - safeZoneY) < safeRadius) continue;
        for (int x = wallX; x < wallX + wallWidth && x < WIDTH - 1; x++) {
            if (x > 1 && x < WIDTH - 1 && abs(x - safeZoneX) >= safeRadius) {
                obstacles.push_back({x, wallY});
            }
        }
    }
    
    for (int i = 0; i < 2; i++) {
        int cornerX = 4 + (rand() % (WIDTH - 12));
        int cornerY = 4 + (rand() % (HEIGHT - 10));
        int armLength = 3 + (rand() % 3);
        if (abs(cornerX - safeZoneX) < safeRadius || abs(cornerY - safeZoneY) < safeRadius) continue;
        for (int x = cornerX; x < cornerX + armLength && x < WIDTH - 1; x++) {
            if (x > 1 && x < WIDTH - 1 && abs(x - safeZoneX) >= safeRadius) {
                obstacles.push_back({x, cornerY});
            }
        }
        for (int y = cornerY; y < cornerY + armLength && y < HEIGHT - 1; y++) {
            if (y > 1 && y < HEIGHT - 1 && abs(y - safeZoneY) >= safeRadius) {
                obstacles.push_back({cornerX, y});
            }
        }
    }
    
    int centerX = 6 + (rand() % (WIDTH - 12));
    int centerY = 4 + (rand() % (HEIGHT - 8));
    int size = 2 + (rand() % 2);
    if (abs(centerX - safeZoneX) >= safeRadius && abs(centerY - safeZoneY) >= safeRadius) {
        for (int x = centerX - size; x <= centerX + size; x++) {
            if (x > 1 && x < WIDTH - 1 && abs(x - safeZoneX) >= safeRadius) {
                obstacles.push_back({x, centerY});
            }
        }
        for (int y = centerY - size; y <= centerY + size; y++) {
            if (y > 1 && y < HEIGHT - 1 && abs(y - safeZoneY) >= safeRadius) {
                obstacles.push_back({centerX, y});
            }
        }
    }
    
    int borderObstacles = 4 + (rand() % 4);
    for (int i = 0; i < borderObstacles; i++) {
        int border = rand() % 4;
        int x, y;
        switch (border) {
            case 0: x = 2 + (rand() % (WIDTH - 4)); y = 1; break;
            case 1: x = 2 + (rand() % (WIDTH - 4)); y = HEIGHT - 2; break;
            case 2: x = 1; y = 2 + (rand() % (HEIGHT - 4)); break;
            case 3: x = WIDTH - 2; y = 2 + (rand() % (HEIGHT - 4)); break;
        }
        if (abs(x - safeZoneX) >= safeRadius && abs(y - safeZoneY) >= safeRadius) {
            obstacles.push_back({x, y});
        }
    }
}

void Game::DrawMenuBorder() {
    colorManager.SetColor(ColorManager::WALL);
    cout << "========================================" << endl;
    colorManager.ResetColor();
}

void Game::ShowMainMenu() {
    system("cls");
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    colorManager.SetColor(ColorManager::MENU_TITLE);
    cout << "========================================" << endl;
    cout << "             SNAKE GAME                 " << endl;
    cout << "========================================" << endl;
    colorManager.ResetColor();
    cout << endl;
    
    cout << "1. Start New Game" << endl;
    cout << "2. View High Scores" << endl;
    cout << "3. How to Play" << endl;
    cout << "4. Exit" << endl;
    cout << endl;
    cout << "Choose option (1-4): ";
    
    char choice = _getch();
    cout << choice << endl;
    
    switch (choice) {
        case '1': return;
        case '2':
            highScore.DisplayScores();
            ShowMainMenu();
            break;
        case '3':
            ShowHelpScreen();
            ShowMainMenu();
            break;
        case '4': exit(0); break;
        default:
            cout << "Invalid choice! Press any key..." << endl;
            _getch();
            ShowMainMenu();
            break;
    }
}

void Game::ShowHelpScreen() {
    system("cls");
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    colorManager.SetColor(ColorManager::MENU_TITLE);
    cout << "========================================" << endl;
    cout << "           SNAKE GAME HELP              " << endl;
    cout << "========================================" << endl;
    colorManager.ResetColor();
    
    cout << endl;
    cout << "OBJECTIVE:" << endl;
    cout << "  Eat food to grow and earn points." << endl;
    cout << "  Avoid hitting walls, obstacles, and the other snake!" << endl;
    cout << endl;
    
    cout << "CONTROLS:" << endl;
    cout << "  Player 1 Controls: Arrow Keys (Up, Down, Left, Right)" << endl;
    cout << "  Player 2 Controls: W, A, S, D Keys" << endl;
    cout << "  P Key            : Pause/Unpause Game" << endl;
    cout << "  X Key            : Exit to Main Menu" << endl;
    cout << endl;
    
    cout << "FOOD TYPES:" << endl;
    colorManager.SetColor(ColorManager::FOOD);
    cout << "  \xDB\xDB Regular Food";
    colorManager.ResetColor();
    cout << " : +10 points" << endl;
    
    colorManager.SetColor(ColorManager::MENU_TITLE);
    cout << "  @@ Golden Food ";
    colorManager.ResetColor();
    cout << " : +30 points (Appears every 5th food!)" << endl;
    cout << endl;
    
    cout << "Press any key to return to menu..." << endl;
    _getch();
}

void Game::Reset() {
    system("cls");
    snakes.clear();
    scores.clear();
    snakes.push_back(Snake(WIDTH, HEIGHT, WIDTH / 2 - 4, HEIGHT / 2, RIGHT));
    snakes.push_back(Snake(WIDTH, HEIGHT, WIDTH / 2 + 4, HEIGHT / 2, LEFT));
    scores.push_back(0);
    scores.push_back(0);
    GenerateObstacles();
    food.GenerateWithObstacles(snakes, obstacles);
    gameOver = false;
    paused = false;
    foodCount = 0;
    losingPlayer = 0;
}

void Game::Draw() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    colorManager.SetColor(ColorManager::WALL);
    for (int i = 0; i < (WIDTH * 2) + 4; i++)
        cout << "#";
    cout << endl;
    
    for (int y = 0; y < HEIGHT; y++) {
        colorManager.SetColor(ColorManager::WALL);
        cout << "##";
        
        for (int x = 0; x < WIDTH; x++) {
            bool isObstacle = false;
            
            for (const auto& obstacle : obstacles) {
                if (x == obstacle.first && y == obstacle.second) {
                    colorManager.SetColor(ColorManager::WALL);
                    cout << "\xDB\xDB";
                    isObstacle = true;
                    break;
                }
            }
            
            if (isObstacle) continue;
            colorManager.SetColor(ColorManager::WALL);
            
            bool isSnakeTile = false;
            for (size_t sIdx = 0; sIdx < snakes.size(); sIdx++) {
                if (x == snakes[sIdx].GetHeadX() && y == snakes[sIdx].GetHeadY()) {
                    colorManager.SetColor((sIdx == 0) ? ColorManager::SNAKE_HEAD : ColorManager::MENU_SELECTED);
                    cout << "\xDB\xDB";
                    isSnakeTile = true;
                    break;
                } else if (snakes[sIdx].IsBody(x, y)) {
                    colorManager.SetColor((sIdx == 0) ? ColorManager::SNAKE_BODY : ColorManager::MENU_TITLE);
                    cout << "\xDB\xDB";
                    isSnakeTile = true;
                    break;
                }
            }
            if (isSnakeTile) continue;

            if (x == food.GetX() && y == food.GetY() && food.IsActive()) {
                colorManager.SetColor(food.GetColor());
                cout << food.GetDisplayChar() << food.GetDisplayChar();
                colorManager.SetColor(ColorManager::WALL);
            } else {
                cout << "  ";
            }
        }
        
        colorManager.SetColor(ColorManager::WALL);
        cout << "##" << endl;
    }
    
    colorManager.SetColor(ColorManager::WALL);
    for (int i = 0; i < (WIDTH * 2) + 4; i++)
        cout << "#";
    cout << endl;
    
    colorManager.ResetColor();
    colorManager.SetColor(ColorManager::SCORE);
    cout << "P1 Score: " << scores[0] << "   |   P2 Score: " << scores[1];
    int padding = 40 - (20 + to_string(scores[0]).length() + to_string(scores[1]).length());
    if (padding > 0) cout << string(padding, ' ');
    cout << endl;
    
    if (paused) {
        colorManager.SetColor(ColorManager::MENU_TITLE);
        PauseGame();
    } else {
        colorManager.SetColor(ColorManager::SCORE);
        cout << "P1: Arrows | P2: WASD | P: Pause | X: Exit" << endl;
    }
    
    cout << "                                                                  " << endl;
    cout << "                                                                  " << endl;
    colorManager.ResetColor();
}

void Game::Input() {
    while (_kbhit()) {
        int key = _getch();
        if (paused) {
            if (key == 'p' || key == 'P') paused = false;
            return;
        }
        if (key == 224) {
            int arrowKey = _getch();
            switch (arrowKey) {
                case 72: snakes[0].ChangeDirection(UP); break;
                case 80: snakes[0].ChangeDirection(DOWN); break;
                case 75: snakes[0].ChangeDirection(LEFT); break;
                case 77: snakes[0].ChangeDirection(RIGHT); break;
            }
        } else {
            switch (key) {
                case 'w': case 'W': snakes[1].ChangeDirection(UP); break;
                case 's': case 'S': snakes[1].ChangeDirection(DOWN); break;
                case 'a': case 'A': snakes[1].ChangeDirection(LEFT); break;
                case 'd': case 'D': snakes[1].ChangeDirection(RIGHT); break;
                case 'p': case 'P': PauseGame(); break;
                case 'x': case 'X': gameOver = true; break;
            }
        }
    }
}

void Game::Logic() {
    if (paused) return;
    for (auto& s : snakes) s.Move();
    
    int head1X = snakes[0].GetHeadX();
    int head1Y = snakes[0].GetHeadY();
    int head2X = snakes[1].GetHeadX();
    int head2Y = snakes[1].GetHeadY();

    bool p1Lost = false;
    bool p2Lost = false;

    if (head1X < 0 || head1X >= WIDTH || head1Y < 0 || head1Y >= HEIGHT) p1Lost = true;
    for (const auto& obstacle : obstacles) {
        if (head1X == obstacle.first && head1Y == obstacle.second) p1Lost = true;
    }
    if (snakes[0].CheckSelfCollision()) p1Lost = true;
    if (snakes[1].IsBody(head1X, head1Y)) p1Lost = true;

    if (head2X < 0 || head2X >= WIDTH || head2Y < 0 || head2Y >= HEIGHT) p2Lost = true;
    for (const auto& obstacle : obstacles) {
        if (head2X == obstacle.first && head2Y == obstacle.second) p2Lost = true;
    }
    if (snakes[1].CheckSelfCollision()) p2Lost = true;
    if (snakes[0].IsBody(head2X, head2Y)) p2Lost = true;

    if (head1X == head2X && head1Y == head2Y) {
        p1Lost = true;
        p2Lost = true;
    }

    if (p1Lost || p2Lost) {
        if (p1Lost && p2Lost) losingPlayer = 3;
        else if (p1Lost) losingPlayer = 1;
        else if (p2Lost) losingPlayer = 2;
        gameOver = true;
        return;
    }

    for (size_t i = 0; i < snakes.size(); i++) {
        int headX = snakes[i].GetHeadX();
        int headY = snakes[i].GetHeadY();
        if (headX == food.GetX() && headY == food.GetY() && food.IsActive()) {
            if (food.GetType() == Food::GOLDEN) {
                Beep(1000, 200);
                Beep(1200, 200);
            } else {
                soundManager.PlayEatSound();
            }
            scores[i] += food.GetPoints();
            snakes[i].Grow();
            foodCount++;
            if (foodCount % 5 == 0) {
                food.GenerateSpecialFood(snakes[0]);
            } else {
                food.GenerateWithObstacles(snakes, obstacles);
            }
        }
    }
}

void Game::PauseGame() {
    paused = true;
    COORD coord = {0, HEIGHT + 4};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "*** GAME PAUSED ***" << endl;
    cout << "Press P to resume" << endl;
}

void Game::EnterHighScore() {
    int pScore = scores[0];
    if (highScore.IsHighScore(pScore)) {
        system("cls");
        colorManager.SetColor(ColorManager::HIGH_SCORE);
        cout << "*** NEW HIGH SCORE! ***" << endl;
        colorManager.ResetColor();
        cout << "Your Score: " << pScore << endl << endl;
        cout << "Enter your name (max 10 letters, letters only): ";
        string name = "";
        char ch;
        bool nameComplete = false;
        while (!nameComplete) {
            ch = _getch();
            if (ch == 13 && name.length() > 0) nameComplete = true;
            else if (ch == 8 && name.length() > 0) { name.pop_back(); cout << "\b \b"; }
            else if (isalpha(ch) && name.length() < 10) { name += toupper(ch); cout << static_cast<char>(toupper(ch)); }
        }
        cout << endl << "Thank you, " << name << "!" << endl;
        Sleep(1000);
        highScore.AddScore(name, pScore);
        system("cls");
    }
}

void Game::GameOverScreen() {
    system("cls");
    colorManager.SetColor(ColorManager::GAME_OVER);
    cout << "########################" << endl;
    if (losingPlayer == 3) {
        cout << "#   BOTH PLAYERS LOST! #" << endl;
    } else if (losingPlayer == 1) {
        cout << "#    PLAYER 1 LOST!    #" << endl;
    } else if (losingPlayer == 2) {
        cout << "#    PLAYER 2 LOST!    #" << endl;
    } else {
        cout << "#      GAME OVER      #" << endl;
    }
    cout << "########################" << endl;
    colorManager.SetColor(ColorManager::SCORE);
    cout << "  P1 Score: " << scores[0] << " | P2 Score: " << scores[1] << endl;
    colorManager.SetColor(ColorManager::GAME_OVER);
    cout << "########################" << endl;
    colorManager.ResetColor();
    cout << endl;
    cout << "1. View High Scores" << endl;
    cout << "2. Play Again" << endl;
    cout << "3. Main Menu" << endl;
    cout << "4. Exit" << endl << endl;
    cout << "Choose option: ";
    char choice;
    cin >> choice;
    switch (choice) {
        case '1': highScore.DisplayScores(); GameOverScreen(); break;
        case '2': Reset(); StartGame(); break;
        case '3': Reset(); gameOver = true; return;
        case '4': exit(0); break;
        default: cout << "Invalid choice...!" << endl; Sleep(1000); GameOverScreen();
    }
}

void Game::StartGame() {
    system("cls");
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    gameOver = false;
    paused = false;
    Draw();
    while (!gameOver) {
        Input();
        Logic();
        Draw();
        Sleep(80);
    }
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    GameOverScreen();
}

void Game::Run() {
    while (true) {
        ShowMainMenu();
        StartGame();
    }
}
