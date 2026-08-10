Snake Game 🐍
A feature-rich, professional Snake game built with C++ for Windows console. This isn't your average Snake game - it's packed with advanced features and demonstrates modern C++ programming practices.

🎮 Features
For Players:
🎯 Colorful Graphics - Beautiful console colors and double-width rendering

🎵 Sound Effects - Audio feedback for game events

🏆 High Score System - Track and save your best scores

🚧 Dynamic Obstacles - Randomly generated obstacles each game

⭐ Special Foods - Golden foods that give extra points

📋 Complete Menu System - Easy navigation with help and instructions

⏸️ Pause Functionality - Take a break anytime

🎛️ Multiple Controls - Support for both WASD and Arrow keys

For Developers:
🏗️ Object-Oriented Architecture - Clean, modular code structure

📁 Multi-file Organization - Proper separation of concerns

🎨 Color Management System - Centralized color handling

🔊 Sound Manager - Easy-to-extend audio system

💾 File I/O System - Persistent high score storage

🎯 Collision Detection - Comprehensive collision system

🔧 Easy Extensibility - Simple to add new features

🚀 Quick Start
Prerequisites
Windows OS

C++ Compiler (MinGW recommended)

Installation & Running
Clone the repository

bash
git clone https://github.com/JagratJani/snake-game-cpp.git
cd snake-game-cpp
Compile the game

bash
g++ -std=c++11 src/*.cpp -o snake_game.exe -static
Run the game

bash
snake_game.exe
Game Controls
W / ↑ - Move Up

S / ↓ - Move Down

A / ← - Move Left

D / → - Move Right

P - Pause Game

X - Exit Game

🛠️ For Developers
Project Structure
text
snake-game-cpp/
├── src/
│   ├── main.cpp          # Program entry point
│   ├── Game.h/cpp        # Main game controller
│   ├── Snake.h/cpp       # Snake logic and movement
│   ├── Food.h/cpp        # Food generation system
│   ├── HighScore.h/cpp   # Score management
│   ├── ColorManager.h/cpp # Console color handling
│   └── SoundManager.h/cpp # Sound effects
├── highscores.txt        # Auto-generated score file
├── README.md            # This file
└── .gitignore           # Git ignore rules

Building from Source

Method 1: Simple Compilation
bash
g++ -std=c++11 src/*.cpp -o snake_game.exe -static

Method 2: Individual Compilation
bash
g++ -std=c++11 -c src/*.cpp
g++ *.o -o snake_game.exe -static

Method 3: With Debug Information
bash
g++ -std=c++11 -g src/*.cpp -o snake_game.exe -static

Architecture Overview

Core Classes

Game - Main controller orchestrating all components

Snake - Handles snake movement, growth, and collision

Food - Manages food generation and placement

HighScore - Persistent score storage and retrieval

ColorManager - Windows console color management

SoundManager - Audio feedback system

Key Design Patterns

Singleton-like - Random initialization

Manager Classes - Color, Sound, HighScore managers

Separation of Concerns - Each class has specific responsibility

Extending the Game

Adding New Food Types

Add to FoodType enum in Food.h

Implement logic in Food.cpp methods

Update Game.cpp to handle new food effects

Adding New Game Modes

Extend Game class with new mode logic

Update menu system in ShowMainMenu()

Add mode-specific drawing and logic

Example: Adding a New Power-up
cpp
// In Food.h
enum FoodType { REGULAR, GOLDEN, SPEED_BOOST };

// In Food.cpp - Update GetPoints(), GetDisplayChar(), GetColor()
// In Game.cpp - Update ApplyFoodEffects() and PlaySpecialFoodSound()

📊 Game Features Deep Dive
Special Food System
Regular Food ($) - +10 points, normal growth

Golden Food (@) - +30 points, appears every 5th food

Visual & Audio Feedback - Different colors and sounds

Obstacle Generation
5 Pattern Types: Walls, L-shapes, plus signs, borders

Safe Zone: Ensures fair starting position

Randomized: Different layout every game

High Score System
File Persistence: Scores saved to highscores.txt

Top 5 Scores: Maintains only best scores

Name Validation: Letters only, max 10 characters

🐛 Troubleshooting
Common Issues
Compilation Errors
bash
# If 'g++' not found:
# Install MinGW and add to PATH

# If Windows API errors:
# Ensure compiling on Windows OS

# If undefined references:
# Make sure all .cpp files are included in compilation

Runtime Issues
No sound: Ensure PC speaker is enabled

Color issues: Works on Windows Command Prompt

File errors: Game creates highscores.txt automatically

Debug Mode
Compile with debug information for troubleshooting:

bash
g++ -std=c++11 -g src/*.cpp -o snake_game_debug.exe -static

📈 Performance
Rendering: Optimized double-width character rendering

Game Loop: 80ms refresh rate for smooth gameplay

Memory: Efficient use of STL containers

File I/O: Lazy loading of high scores

🎓 Learning Outcomes
This project demonstrates:

C++ OOP Principles - Classes, encapsulation, inheritance

Windows API Usage - Console manipulation, sounds

File I/O Operations - Reading/writing persistent data

Game Development - Game loops, collision detection, state management

Software Architecture - Modular design, separation of concerns

🤝 Contributing
Fork the repository

Create a feature branch (git checkout -b feature/amazing-feature)

Commit your changes (git commit -m 'Add amazing feature')

Push to the branch (git push origin feature/amazing-feature)

Open a Pull Request

🙏 Acknowledgments
Inspired by classic Snake games

Windows Console API documentation

C++ Standard Template Library

Happy Gaming! 🎮 | Happy Coding! 💻

For questions or support, please open an issue on GitHub.