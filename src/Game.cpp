#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <algorithm>

using namespace std;

Game::Game() : snake(WIDTH, HEIGHT), food(WIDTH, HEIGHT), score(0), gameOver(false), paused(false) {
    food.Generate(snake);
}

void Game::DrawMenuBorder() {
    system("cls");
    
    // Draw a fancy border for the menu
    string topBottom = "===================================================";
    string side = "|                                                 |";
    
    cout << topBottom << endl;
    for (int i = 0; i < 25; i++) {
        cout << side << endl;
    }
    cout << topBottom << endl;
}

void Game::ShowMainMenu() {
    static int selectedOption = 0;
    const int TOTAL_OPTIONS = 4;
    string options[TOTAL_OPTIONS] = {
        "Start Game",
        "View High Scores", 
        "Help",
        "Exit"
    };
    
    while (true) {
        // Draw everything each time, but only when needed
        DrawMenuBorder();
        
        COORD coord = {5, 3};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "           <<< SNAKE GAME >>>" << endl;
        
        coord.Y += 4;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "Use W/S or Arrow Keys to navigate" << endl;
        
        coord.Y += 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        
        // Menu options
        for (int i = 0; i < TOTAL_OPTIONS; i++) {
            if (i == selectedOption) {
                cout << "    > " << options[i] << " <" << endl;
            } else {
                cout << "      " << options[i] << "   " << endl;
            }
            coord.Y += 1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
        
        coord.Y += 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "Press ENTER to select" << endl;
        
        // Wait for input without rapid redrawing
        while (!_kbhit()) {
            Sleep(100); // Wait for input without redrawing
        }
        
        int key = _getch();
        
        if (key == 224) { // Arrow keys
            int arrowKey = _getch();
            if (arrowKey == 72) { // Up arrow
                selectedOption = (selectedOption - 1 + TOTAL_OPTIONS) % TOTAL_OPTIONS;
            } else if (arrowKey == 80) { // Down arrow
                selectedOption = (selectedOption + 1) % TOTAL_OPTIONS;
            }
        } else {
            switch (key) {
                case 'w': case 'W':
                    selectedOption = (selectedOption - 1 + TOTAL_OPTIONS) % TOTAL_OPTIONS;
                    break;
                case 's': case 'S':
                    selectedOption = (selectedOption + 1) % TOTAL_OPTIONS;
                    break;
                case 13: // Enter key
                    switch (selectedOption) {
                        case 0: return; // Start Game
                        case 1: 
                            highScore.DisplayScores();
                            break;
                        case 2: 
                            ShowHelpScreen();
                            break;
                        case 3: 
                            exit(0);
                            break;
                    }
                    break;
                case 'x': case 'X':
                    exit(0);
                    break;
            }
        }
    }
}

void Game::ShowHelpScreen() {
    DrawMenuBorder();
    
    COORD coord = {5, 3};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    cout << "          <<< HOW TO PLAY >>>          " << endl;

    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "CONTROLS:" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  W / Up Arrow   - Move Up" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  S / Down Arrow - Move Down" << endl;

    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  A / Left Arrow - Move Left" << endl;

    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  D / Right Arrow - Move Right" << endl;

    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  P - Pause Game" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  X - Exit Game" << endl;
    
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "GAME RULES:" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  1 Eat food (*) to grow and earn points" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  2 Avoid hitting walls or yourself" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  3 Each food gives 10 points" << endl;
    
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "Press any key to return to menu..." << endl;
    
    _getch();
}

void Game::Reset() {
    system("cls");
    snake = Snake(WIDTH, HEIGHT);
    food.Generate(snake);
    score = 0;
    gameOver = false;
    paused = false;
}

void Game::Draw() {
    static string buffer;
    buffer.clear();
    
    // Game board
    buffer.append(WIDTH + 2, '#');
    buffer += '\n';
    
    for (int y = 0; y < HEIGHT; y++) {
        buffer += '#';
        
        for (int x = 0; x < WIDTH; x++) {
            if (x == snake.GetHeadX() && y == snake.GetHeadY())
                buffer += 'O';
            else if (snake.IsBody(x, y))
                buffer += 'o';
            else if (x == food.GetX() && y == food.GetY())
                buffer += '*';
            else
                buffer += ' ';
        }
        
        buffer += "#\n";
    }
    
    buffer.append(WIDTH + 2, '#');
    buffer += '\n';
    
    // Score line - fixed width
    buffer += "Score: " + to_string(score);
    buffer.append(30 - (7 + to_string(score).length()), ' '); // Pad with spaces
    buffer += '\n';
    
    // Status line - fixed width (BOTH messages always show)
    if (paused) {
        buffer += "*** GAME PAUSED *** \n\n  Press P to resume";
        buffer.append(10, ' '); // Pad with spaces
    } else {
        // Show both High Score Potential AND Controls
        if (highScore.IsHighScore(score)) {
            buffer += "High Score Potential! | Controls: WASD/Arrows, P=Pause, X=Exit";
        } else {
            buffer += "Controls: WASD/Arrows, P=Pause, X=Exit";
            buffer.append(20, ' '); // Pad with spaces
        }
    }
    buffer += '\n';
    
    // Clear any remaining lines
    buffer += "                                        \n";
    
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << buffer;
}

void Game::Input() {
    if (_kbhit()) {
        int key = _getch();
        
        if (paused) {
            if (key == 'p' || key == 'P') {
                paused = false;
            }
            return;
        }
        
        if (key == 224) {
            int arrowKey = _getch();
            switch (arrowKey) {
                case 72: snake.ChangeDirection(UP); break;
                case 80: snake.ChangeDirection(DOWN); break;
                case 75: snake.ChangeDirection(LEFT); break;
                case 77: snake.ChangeDirection(RIGHT); break;
            }
        } else {
            switch (key) {
                case 'w': case 'W': snake.ChangeDirection(UP); break;
                case 's': case 'S': snake.ChangeDirection(DOWN); break;
                case 'a': case 'A': snake.ChangeDirection(LEFT); break;
                case 'd': case 'D': snake.ChangeDirection(RIGHT); break;
                case 'p': case 'P': PauseGame(); break;
                case 'x': case 'X': gameOver = true; break;
            }
        }
    }
}

void Game::Logic() {
    if (paused) return;
    
    snake.Move();
    
    int headX = snake.GetHeadX();
    int headY = snake.GetHeadY();
    
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
        EnterHighScore();
        gameOver = true;
        return;
    }
    
    if (snake.CheckSelfCollision()) {
        EnterHighScore();
        gameOver = true;
        return;
    }
    
    if (headX == food.GetX() && headY == food.GetY()) {
        soundManager.PlayEatSound();  // Food eating sound
        snake.Grow();
        score += 10;
        food.Generate(snake);
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
    if (highScore.IsHighScore(score)) {
        system("cls");
        cout << "###############################" << endl;
        cout << "#      NEW HIGH SCORE!       #" << endl;
        cout << "###############################" << endl;
        cout << "     Your Score: " << score << endl;
        cout << endl;
        cout << "Enter your name (3 letters): ";
        
        string name;
        cin >> name;
        
        if (name.length() > 3) name = name.substr(0, 3);
        for (char& c : name) c = toupper(c);
        if (name.empty()) name = "AAA";
        
        highScore.AddScore(name, score);
    }
}

void Game::GameOverScreen() {
    system("cls");
    cout << "########################" << endl;
    cout << "#      GAME OVER      #" << endl;
    cout << "########################" << endl;
    cout << "     Final Score: " << score << endl;
    
    if (highScore.IsHighScore(score)) {
        cout << "   NEW HIGH SCORE!   " << endl;
    }
    
    cout << "########################" << endl;
    cout << endl;
    cout << "1. View High Scores" << endl;
    cout << "2. Play Again" << endl;
    cout << "3. Main Menu" << endl;
    cout << "4. Exit" << endl;
    cout << endl;
    cout << "Choose option: ";
    
    char choice;
    cin >> choice;
    
    switch (choice) {
        case '1':
            highScore.DisplayScores();
            GameOverScreen();
            break;
        case '2':
            Reset();
            StartGame();
            break;
        case '3':
            Reset();
            gameOver = true;
            return;
        case '4':
            exit(0);
            break;
        default:
            cout << "Invalid choice...!" << endl;
            Sleep(1000);
            GameOverScreen();
    }
}

// Start game without showing menu
void Game::StartGame() {
    // Clear screen and setup for gameplay
    system("cls");
    
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    gameOver = false; // Ensure game is not over
    paused = false;   // Ensure game is not paused
    
    Draw();
    
    while (!gameOver) {
        Input();
        Logic();
        Draw();
        Sleep(150);
    }
    
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    
    GameOverScreen();
}

void Game::Run() {
    while (true) {
        // Show main menu first
        ShowMainMenu();
        
        // After menu, start the game
        StartGame();
    }
}