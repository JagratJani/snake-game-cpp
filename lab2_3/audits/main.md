# Code Smell Audit — Main Branch

This report documents code smells identified on the `main` branch of the Snake Game repository.

## Confirmed Findings

### 1. Divergent Change at `src/Game.h:17`
- **Smell**: Divergent Change at `src/Game.h:17`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.h:17`
- **Explanation**: The assumption that there is exactly one snake (`Snake snake;`) is hardcoded across multiple `Game` methods (`Input`, `Logic`, `Draw`, `Reset`, `Food::GenerateWithObstacles`). Modifying snake logic or adding player instances forces edits across unrelated game loop functions.
- **Refactoring Direction**: Encapsulate snakes into a collection or manager so `Game` logic iterates over active snakes (`refactor-moving-features`).

### 2. Large Class at `src/Game.h:12`
- **Smell**: Large Class at `src/Game.h:12`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.h:12`
- **Explanation**: `Game` handles rendering, user input, collision logic, food spawning, obstacle generation, high score handling, pause state, and menu rendering.
- **Refactoring Direction**: Extract rendering into visual components and separate game loop state from menu presentation (`refactor-moving-features`).

### 3. Long Method at `src/Game.cpp:17`
- **Smell**: Long Method at `src/Game.cpp:17`
- **Severity**: HIGH
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:17`
- **Explanation**: `Game::GenerateObstacles()` is 111 lines long with 5 repetitive nested loop blocks creating vertical walls, horizontal walls, L-shapes, plus signs, and border obstacles.
- **Refactoring Direction**: Extract Method for each individual obstacle pattern (`refactor-composing-methods`).

### 4. Long Method at `src/Game.cpp:143`
- **Smell**: Long Method at `src/Game.cpp:143`
- **Severity**: MEDIUM
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:143`
- **Explanation**: `Game::ShowMainMenu()` is 89 lines long, combining menu loop management, cursor repositioning, string formatting, keyboard reading via `_getch()`, and option routing.
- **Refactoring Direction**: Extract input polling and option action handlers from rendering (`refactor-composing-methods`).

### 5. Long Method at `src/Game.cpp:235`
- **Smell**: Long Method at `src/Game.cpp:235`
- **Severity**: MEDIUM
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.cpp:235`
- **Explanation**: `Game::ShowHelpScreen()` is 75 lines long consisting of repeated console cursor positioning and string printing.
- **Refactoring Direction**: Extract line printing into a helper or data array (`refactor-composing-methods`).

### 6. Primitive Obsession at `src/Game.h:22`
- **Smell**: Primitive Obsession at `src/Game.h:22`
- **Severity**: MEDIUM
- **Confidence Level**: C3 (High)
- **Location**: `src/Game.h:22`
- **Explanation**: Obstacles are represented using `std::vector<std::pair<int, int>>` rather than a domain coordinate or obstacle struct.
- **Refactoring Direction**: Replace primitives with a structured coordinate/obstacle type (`refactor-organizing-data`).
