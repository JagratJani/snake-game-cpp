# Code Smell Audit — Lab-1 Head Branch

This report documents code smells identified on the `feat/multiplayer` branch head (Lab-1 implementation).

## Confirmed Findings

### 1. Long Method at `src/Game.cpp:455`
- **Smell**: Long Method at `src/Game.cpp:455`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:455`
- **Explanation**: `Game::Logic()` was expanded by 35 lines in Lab 1 to handle dual-snake movement, wall collisions, obstacle collisions, self collisions, cross-snake collisions, head-to-head collisions, and multi-player food eating.
- **Refactoring Direction**: Extract collision detection methods (`refactor-composing-methods`).

### 2. Long Method at `src/Game.cpp:334`
- **Smell**: Long Method at `src/Game.cpp:334`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:334`
- **Explanation**: `Game::Draw()` was expanded in Lab 1 to render both snakes (`snake` and `snake2`) using different color attributes, rendering shared food, and outputting dual score headers.
- **Refactoring Direction**: Extract entity drawing loop helpers (`refactor-composing-methods`).

### 3. Long Method at `src/Game.cpp:428`
- **Smell**: Long Method at `src/Game.cpp:428`
- **Severity**: MEDIUM
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:428`
- **Explanation**: `Game::Input()` was expanded in Lab 1 to poll input buffer via `while (_kbhit())` and branch key bindings for Player 1 (Arrow keys) and Player 2 (WASD).
- **Refactoring Direction**: Separate key handling into player input mappers (`refactor-moving-features`).

### 4. Duplicate Code at `src/Snake.cpp:16`
- **Smell**: Duplicate Code at `src/Snake.cpp:16`
- **Severity**: MEDIUM
- **Confidence Level**: C3 (High)
- **Location**: `src/Snake.cpp:16`
- **Explanation**: The overloaded constructor `Snake::Snake(int width, int height, int startX, int startY, Direction startDir)` duplicates loop logic and body initialization from the default constructor.
- **Refactoring Direction**: Consolidate constructors or use default parameters (`refactor-composing-methods`).

### 5. Divergent Change at `src/Game.h:12`
- **Smell**: Divergent Change at `src/Game.h:12`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.h:12`
- **Explanation**: `Game` continues to hold all responsibilities (rendering, input, logic, screen state, food checks) without modular separation.
- **Refactoring Direction**: Extract subsystems (`refactor-moving-features`).

### 6. Long Method at `src/Game.cpp:17`
- **Smell**: Long Method at `src/Game.cpp:17`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:17`
- **Explanation**: `Game::GenerateObstacles()` remains 111 lines long with 5 repetitive nested loop patterns.
- **Refactoring Direction**: Extract pattern generator methods (`refactor-composing-methods`).

### 7. Primitive Obsession at `src/Game.h:22`
- **Smell**: Primitive Obsession at `src/Game.h:22`
- **Severity**: MEDIUM
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.h:22`
- **Explanation**: Obstacles remain `std::vector<std::pair<int, int>>`.
- **Refactoring Direction**: Replace with coordinate objects (`refactor-organizing-data`).
