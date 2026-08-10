#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>

using namespace std;

Game::Game() : snake(WIDTH, HEIGHT, WIDTH/3, HEIGHT/2), snake2(WIDTH, HEIGHT, WIDTH*2/3, HEIGHT/2), food(WIDTH, HEIGHT), score(0), score2(0), gameOver(false), paused(false), foodCount(0), loserPlayer(0) {
    GenerateObstacles();
    food.GenerateWithObstacles(snake, snake2, obstacles);
}

void Game::GenerateObstacles() {
    obstacles.clear();
    
    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Define safe zone in the center where snake starts
    int safeZoneX = WIDTH / 2;
    int safeZoneY = HEIGHT / 2;
    int safeRadius = 4;
    
    // Pattern 1: Vertical walls
    for (int i = 0; i < 3; i++) {
        int wallX = 5 + (rand() % (WIDTH - 10));
        int wallY = 3 + (rand() % (HEIGHT - 6));
        int wallHeight = 3 + (rand() % 4);
        
        // Check if wall is too close to safe zone
        if (abs(wallX - safeZoneX) < safeRadius) continue;
        
        for (int y = wallY; y < wallY + wallHeight && y < HEIGHT - 1; y++) {
            // Don't place on borders and ensure it's not in safe zone
            if (y > 1 && y < HEIGHT - 1 && abs(y - safeZoneY) >= safeRadius) {
                obstacles.push_back({wallX, y});
            }
        }
    }
    
    // Pattern 2: Horizontal walls
    for (int i = 0; i < 3; i++) {
        int wallY = 5 + (rand() % (HEIGHT - 10));
        int wallX = 3 + (rand() % (WIDTH - 6));
        int wallWidth = 4 + (rand() % 5);
        
        // Check if wall is too close to safe zone
        if (abs(wallY - safeZoneY) < safeRadius) continue;
        
        for (int x = wallX; x < wallX + wallWidth && x < WIDTH - 1; x++) {
            // Don't place on borders and ensure it's not in safe zone
            if (x > 1 && x < WIDTH - 1 && abs(x - safeZoneX) >= safeRadius) {
                obstacles.push_back({x, wallY});
            }
        }
    }
    
    // Pattern 3: L-shaped corners
    for (int i = 0; i < 2; i++) {
        int cornerX = 3 + (rand() % (WIDTH - 8));
        int cornerY = 3 + (rand() % (HEIGHT - 8));
        
        // Check if corner is too close to safe zone
        if (abs(cornerX - safeZoneX) < safeRadius + 2 || abs(cornerY - safeZoneY) < safeRadius + 2) continue;
        
        // Create L-shape (3 blocks horizontal, 3 blocks vertical)
        for (int x = cornerX; x < cornerX + 3 && x < WIDTH - 1; x++) {
            obstacles.push_back({x, cornerY});
        }
        for (int y = cornerY; y < cornerY + 3 && y < HEIGHT - 1; y++) {
            obstacles.push_back({cornerX, y});
        }
    }
    
    // Pattern 4: Plus signs (+)
    for (int i = 0; i < 2; i++) {
        int centerX = 6 + (rand() % (WIDTH - 12));
        int centerY = 6 + (rand() % (HEIGHT - 12));
        
        // Check if plus is too close to safe zone
        if (abs(centerX - safeZoneX) < safeRadius + 1 || abs(centerY - safeZoneY) < safeRadius + 1) continue;
        
        // Create plus shape
        obstacles.push_back({centerX, centerY});
        obstacles.push_back({centerX - 1, centerY});
        obstacles.push_back({centerX + 1, centerY});
        obstacles.push_back({centerX, centerY - 1});
        obstacles.push_back({centerX, centerY + 1});
    }
    
    // Pattern 5: Border obstacles (partial walls near edges)
    // Top border obstacles
    for (int x = 3; x < WIDTH - 3; x += 4) {
        if (abs(x - safeZoneX) > safeRadius) {
            obstacles.push_back({x, 2});
        }
    }
    
    // Bottom border obstacles
    for (int x = 4; x < WIDTH - 4; x += 4) {
        if (abs(x - safeZoneX) > safeRadius) {
            obstacles.push_back({x, HEIGHT - 3});
        }
    }
    
    // Left border obstacles
    for (int y = 3; y < HEIGHT - 3; y += 4) {
        if (abs(y - safeZoneY) > safeRadius) {
            obstacles.push_back({2, y});
        }
    }
    
    // Right border obstacles
    for (int y = 4; y < HEIGHT - 4; y += 4) {
        if (abs(y - safeZoneY) > safeRadius) {
            obstacles.push_back({WIDTH - 3, y});
        }
    }
    
    // Remove any duplicates
    sort(obstacles.begin(), obstacles.end());
    obstacles.erase(unique(obstacles.begin(), obstacles.end()), obstacles.end());
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
        DrawMenuBorder();
        
        COORD coord = {5, 3};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        
        // Title in yellow
        colorManager.SetColor(ColorManager::MENU_TITLE);
        cout << "           <<< SNAKE GAME >>>" << endl;
        colorManager.ResetColor();
        
        coord.Y += 4;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "Use W/S or Arrow Keys to navigate" << endl;
        
        coord.Y += 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        
        // Menu options with colors
        for (int i = 0; i < TOTAL_OPTIONS; i++) {
            if (i == selectedOption) {
                colorManager.SetColor(ColorManager::MENU_SELECTED);
                cout << "    > " << options[i] << " <" << endl;
            } else {
                colorManager.SetColor(ColorManager::MENU_NORMAL);
                cout << "      " << options[i] << "   " << endl;
            }
            coord.Y += 1;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        }
        
        colorManager.ResetColor();
        
        coord.Y += 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << "Press ENTER to select" << endl;
        
        // Wait for input without rapid redrawing
        while (!_kbhit()) {
            Sleep(100);
        }
        
        int key = _getch();
        
        if (key == 224) {
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
                    soundManager.PlayMenuSelectSound();
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

    // Title in yellow
    colorManager.SetColor(ColorManager::MENU_TITLE);
    cout << "          <<< HOW TO PLAY >>>          " << endl;
    colorManager.ResetColor();

    coord.Y += 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    // Section headers in cyan
    colorManager.SetColor(ColorManager::MENU_SELECTED);
    cout << "CONTROLS:" << endl;
    colorManager.ResetColor();
    
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
    
    colorManager.SetColor(ColorManager::MENU_SELECTED);
    cout << "GAME RULES:" << endl;
    colorManager.ResetColor();
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  1 Eat food (*) to grow and earn points" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  2 Avoid hitting walls or yourself" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  3 Avoid obstacles (X) - random in each game" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  4 Larger 30x20 game area" << endl;
    
    coord.Y += 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "  5 Each food gives 10 points" << endl;
    
    coord.Y += 3;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    cout << "Press any key to return to menu..." << endl;
    
    _getch();
}

void Game::Reset() {
    system("cls");
    snake = Snake(WIDTH, HEIGHT, WIDTH/3, HEIGHT/2);
    snake2 = Snake(WIDTH, HEIGHT, WIDTH*2/3, HEIGHT/2);
    GenerateObstacles();
    food.GenerateWithObstacles(snake, snake2, obstacles);
    score = 0;
    score2 = 0;
    gameOver = false;
    paused = false;
    foodCount = 0; // Reset food counter
    loserPlayer = 0;
}

void Game::Draw() {
    // Move cursor to top-left for smooth rendering
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    // Draw top border (double width)
    colorManager.SetColor(ColorManager::WALL);
    for (int i = 0; i < (WIDTH * 2) + 4; i++)
        cout << "#";
    cout << endl;
    
    // Draw game area
    for (int y = 0; y < HEIGHT; y++) {
        // Left border
        colorManager.SetColor(ColorManager::WALL);
        cout << "##";
        
        for (int x = 0; x < WIDTH; x++) {
            bool isObstacle = false;
            
            // Check if this position is an obstacle
            for (const auto& obstacle : obstacles) {
                if (x == obstacle.first && y == obstacle.second) {
                    colorManager.SetColor(ColorManager::WALL);
                    cout << "\xDB\xDB";  // Double width block obstacles
                    isObstacle = true;
                    break;
                }
            }
            
            if (isObstacle) {
                continue;
            }
            
            // Reset to wall color for empty spaces
            colorManager.SetColor(ColorManager::WALL);
            
            if (x == snake.GetHeadX() && y == snake.GetHeadY()) {
                colorManager.SetColor(ColorManager::SNAKE_HEAD);
                cout << "\xDB\xDB";  // Double width block head
            }
            else if (snake.IsBody(x, y)) {
                colorManager.SetColor(ColorManager::SNAKE_BODY);
                cout << "\xDB\xDB";  // Double width block body
            }
            else if (x == snake2.GetHeadX() && y == snake2.GetHeadY()) {
                colorManager.SetColor(ColorManager::SNAKE_HEAD);
                cout << "\xDB\xDB";  
            }
            else if (snake2.IsBody(x, y)) {
                colorManager.SetColor(ColorManager::SNAKE_BODY);
                cout << "\xDB\xDB";  
            }
            else if (x == food.GetX() && y == food.GetY() && food.IsActive()) {
                // Use food's own color and character
                colorManager.SetColor(food.GetColor());
                cout << food.GetDisplayChar() << food.GetDisplayChar(); // Double width
                colorManager.SetColor(ColorManager::WALL);
}
            else {
                cout << "  ";  // Double width space
            }
        }
        
        // Right border
        colorManager.SetColor(ColorManager::WALL);
        cout << "##" << endl;
    }
    
    // Draw bottom border (double width)
    colorManager.SetColor(ColorManager::WALL);
    for (int i = 0; i < (WIDTH * 2) + 4; i++)
        cout << "#";
    cout << endl;
    
    // Reset color for text
    colorManager.ResetColor();
    
    // Score with color - Bright White
    colorManager.SetColor(ColorManager::SCORE);
    string scoreStr = "P1: " + to_string(score) + " | P2: " + to_string(score2);
    cout << scoreStr;
    int padding = 30 - scoreStr.length();
    if (padding > 0) cout << string(padding, ' ');
    cout << endl;
    
    // Status line with colors
    if (paused) {
        colorManager.SetColor(ColorManager::MENU_TITLE);
        PauseGame();
    } else {
        if (highScore.IsHighScore(std::max(score, score2))) {
            colorManager.SetColor(ColorManager::HIGH_SCORE);
            cout << "High Score Potential! | Controls: WASD/Arrows, P=Pause, X=Exit" << endl;
        } else {
            colorManager.SetColor(ColorManager::SCORE);
            cout << "Controls: WASD/Arrows, P=Pause, X=Exit" << endl;
        }
    }
    
    // Clear any remaining lines to prevent ghost text
    cout << "                                                                  " << endl;
    cout << "                                                                  " << endl;
    
    // Reset to default color
    colorManager.ResetColor();
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
                case 'w': case 'W': snake2.ChangeDirection(UP); break;
                case 's': case 'S': snake2.ChangeDirection(DOWN); break;
                case 'a': case 'A': snake2.ChangeDirection(LEFT); break;
                case 'd': case 'D': snake2.ChangeDirection(RIGHT); break;
                case 'p': case 'P': PauseGame(); break;
                case 'x': case 'X': gameOver = true; break;
            }
        }
    }
}

void Game::Logic() {
    if (paused) return;
    
    snake.Move();
    snake2.Move();
    
    int headX = snake.GetHeadX();
    int headY = snake.GetHeadY();
    int head2X = snake2.GetHeadX();
    int head2Y = snake2.GetHeadY();

    bool p1Lost = false;
    bool p2Lost = false;
    
    // Check wall collisions
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) p1Lost = true;
    if (head2X < 0 || head2X >= WIDTH || head2Y < 0 || head2Y >= HEIGHT) p2Lost = true;
    
    // Check obstacle collisions
    for (const auto& obstacle : obstacles) {
        if (headX == obstacle.first && headY == obstacle.second) p1Lost = true;
        if (head2X == obstacle.first && head2Y == obstacle.second) p2Lost = true;
    }
    
    // Check self collision
    if (snake.CheckSelfCollision()) p1Lost = true;
    if (snake2.CheckSelfCollision()) p2Lost = true;

    // Check collision with each other
    if (headX == head2X && headY == head2Y) {
        p1Lost = true;
        p2Lost = true;
    } else {
        if (snake2.IsBody(headX, headY)) p1Lost = true;
        if (snake.IsBody(head2X, head2Y)) p2Lost = true;
    }

    if (p1Lost && p2Lost) loserPlayer = 3;
    else if (p1Lost) loserPlayer = 1;
    else if (p2Lost) loserPlayer = 2;

    if (p1Lost || p2Lost) {
        EnterHighScore();
        gameOver = true;
        return;
    }
    
    // Check food collision
    bool p1Ate = (headX == food.GetX() && headY == food.GetY() && food.IsActive());
    bool p2Ate = (head2X == food.GetX() && head2Y == food.GetY() && food.IsActive());

    if (p1Ate || p2Ate) {
        // Play sound based on food type
        if (food.GetType() == Food::GOLDEN) {
            Beep(1000, 200); // Special sound for golden food
            Beep(1200, 200);
        } else {
            soundManager.PlayEatSound(); // Regular sound
        }
        
        // Add points based on food type
        if (p1Ate) {
            score += food.GetPoints();
            snake.Grow();
        }
        if (p2Ate) {
            score2 += food.GetPoints();
            snake2.Grow();
        }
        
        // Increment food counter
        foodCount++;
        
        // Every 5th food is golden, others are regular
        if (foodCount % 5 == 0) {
            // Spawn golden food
            food.GenerateSpecialFood(snake, snake2);
        } else {
            // Spawn regular food
            food.GenerateWithObstacles(snake, snake2, obstacles);
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
    int maxScore = std::max(score, score2);
    if (highScore.IsHighScore(maxScore)) {
        system("cls");
        
        // Show simple prompt without the fancy border
        colorManager.SetColor(ColorManager::HIGH_SCORE);
        cout << "*** NEW HIGH SCORE! ***" << endl;
        colorManager.ResetColor();
        
        cout << "High Score: " << maxScore << endl;
        cout << endl;
        cout << "Enter your name (max 10 letters, letters only): ";
        
        string name = "";
        char ch;
        bool nameComplete = false;
        
        while (!nameComplete) {
            ch = _getch(); // Get character without echo
            
            if (ch == 13 && name.length() > 0) { // Enter key
                nameComplete = true;
            }
            else if (ch == 8 && name.length() > 0) { // Backspace
                name.pop_back();
                cout << "\b \b"; // Erase the character from console
            }
            else if (isalpha(ch) && name.length() < 10) { // Only letters and max 10 chars
                name += toupper(ch);
                cout << static_cast<char>(toupper(ch)); // Echo the character
            }
            // Ignore all other characters (numbers, symbols, etc.)
        }
        
        cout << endl;
        cout << "Thank you, " << name << "!" << endl;
        Sleep(1000);
        
        highScore.AddScore(name, maxScore);
        
        // Clear the screen after name entry
        system("cls");
    }
}

void Game::GameOverScreen() {
    system("cls");
    
    int maxScore = std::max(score, score2);
    bool isNewHighScore = highScore.IsHighScore(maxScore);
    
    if (isNewHighScore) {
        // Show NEW HIGH SCORE in green instead of GAME OVER
        colorManager.SetColor(ColorManager::HIGH_SCORE);
        cout << "##############################" << endl;
        cout << "#       NEW HIGH SCORE!     #" << endl;
        cout << "##############################" << endl;
        
        // Score in GREEN for new high score
        colorManager.SetColor(ColorManager::HIGH_SCORE);
        cout << "  P1 Score: " << score << " | P2 Score: " << score2 << endl;
        if (loserPlayer == 1) cout << "     Player 1 lost!" << endl;
        else if (loserPlayer == 2) cout << "     Player 2 lost!" << endl;
        else if (loserPlayer == 3) cout << "     Both players lost!" << endl;
        
        // Bottom border in green
        colorManager.SetColor(ColorManager::HIGH_SCORE);
        cout << "##############################" << endl;
    } else {
        // Show regular GAME OVER in red
        colorManager.SetColor(ColorManager::GAME_OVER);
        cout << "########################" << endl;
        cout << "#      GAME OVER      #" << endl;
        cout << "########################" << endl;
        
        // Score in White for regular game over
        colorManager.SetColor(ColorManager::SCORE);
        cout << "  P1 Score: " << score << " | P2 Score: " << score2 << endl;
        if (loserPlayer == 1) cout << "     Player 1 lost!" << endl;
        else if (loserPlayer == 2) cout << "     Player 2 lost!" << endl;
        else if (loserPlayer == 3) cout << "     Both players lost!" << endl;
        
        colorManager.SetColor(ColorManager::GAME_OVER);
        cout << "########################" << endl;
    }
    
    colorManager.ResetColor();
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
    
    gameOver = false;
    paused = false;
    
    Draw();
    
    // Simple game loop
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
        // Show main menu first
        ShowMainMenu();
        
        // After menu, start the game
        StartGame();
    }
}