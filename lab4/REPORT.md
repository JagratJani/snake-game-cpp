# Lab 4 — Group A

| | |
|---|---|
| Repository | https://github.com/JagratJani/snake-game-cpp |
| Base tag | `lab4-base` at commit `54d6b92` |
| Pull request | https://github.com/JagratJani/snake-game-cpp/pulls |

---

## 1. Five rules — [5]

Written before opening the source. Behaviour, with an observable outcome.

| # | Rule |
|---|---|
| 1 | Wall Collision: When the snake's head moves out of grid boundaries (x < 0, x >= maxX, y < 0, or y >= maxY), a collision occurs resulting in a game over condition. |
| 2 | Self Collision: When the snake's head position overlaps with any of its body segments, self-collision is detected resulting in a game over condition. |
| 3 | Food Consumption & Growth: Consuming regular food increases the player's score by 10 points and grows the snake by 1 body segment on the next move, while golden food grants 30 points. |
| 4 | Direction Reversal Prevention: The snake cannot instantly reverse 180 degrees into the exact opposite direction (e.g., RIGHT to LEFT or UP to DOWN); attempting an invalid reversal leaves the direction unchanged. |
| 5 | Food Spawn Validity: Newly generated food must be placed at random grid coordinates that do not overlap with the snake's head, body segments, or existing obstacles. |

If you could not state one of your own game's rules without going to look, say which and why. It costs no marks.

N/A — All rules were defined directly from standard Snake game mechanics and user-observable behavior.

---

## 2. What you could test, and what stopped you — [10]

No source changes in this part. Every `file:line` below is a line in `lab4-base`.

| # | Rule | Test written? | Blocking dependency (`file:line` + what it is) |
|---|---|---|---|
| 1 | Wall Collision | Yes | None |
| 2 | Self Collision | Yes | None |
| 3 | Food Consumption & Growth | Yes | None |
| 4 | Direction Reversal Prevention | Yes | None |
| 5 | Food Spawn Validity | No | `src/Food.cpp:32` — non-deterministic output from `std::rand()` called directly inside `Food::GenerateWithObstacles` |

> **Rules testable without modifying the source: 4 / 5**

---

## 3. Coverage, and what it missed — [6]

| | |
|---|---|
| Line coverage | 69.89 % (65/93 lines in Snake.cpp and Food.cpp) |
| Branch coverage | 56.47 % (48/85 branches taken in Snake.cpp and Food.cpp) |
| Command used | `gcov -b Snake.cpp Food.cpp` |

**One rule that is executed by the suite but not verified by it:**

| | |
|---|---|
| Rule | Rule 3: Single-segment growth per food item (Growth state resets after 1 move) |
| Line that runs | `src/Snake.cpp:41` (`grown = false;` executed inside `Snake::Move()`) |
| The assertion that is missing | Asserting that a SECOND call to `snake.Move()` after eating food does NOT increase body size further (`EXPECT_EQ(snake.GetBody().size(), initial_size + 1)` after the 2nd move). |

---

## 4. The seam — [10]

| | |
|---|---|
| Rule made testable | Rule 5: Food Spawn Validity (Deterministic random placement) |
| Commit 1 (seam) | `0d173d2` (Refactor: Introduce function pointer seam for std::rand in Food) |
| Commit 2 (test) | `b509de7` (Test: Add unit tests for rules and seam using GoogleTest harness) |
| Seam kind | object |
| Enabling point | `Food::randSource` static member function pointer in `Food.h` / `Food.cpp` |
| What production code gave up | Nothing. `Food::randSource` defaults to `std::rand` at startup, preserving identical runtime behavior without performance overhead or breaking callers. |

The last row is graded. If the honest answer is "nothing", write that and say why the seam cost nothing here.

---

## 5. The double — [4]

| | |
|---|---|
| What you passed through the seam | stub |
| The method under test | `Food::GenerateWithObstacles` |

Two sentences: The test passed a deterministic lambda function through the `randSource` seam to return controlled coordinate values rather than random numbers. Because the collaborator (`randSource`) was queried for values (asked a question) rather than being verified for specific side-effect invocations or expectations, the double functions strictly as a stub.

---

## 6. Two smells in your own tests — [5]

| | Smell | `file:line` | One-line fix |
|---|---|---|---|
| 1 | Magic Numbers / Hardcoded Constants | `lab4/test_snake_rules.cpp:25` | Extract hardcoded dimension arguments `20, 20` into named `constexpr int BOARD_WIDTH = 20;`. |
| 2 | Assertion Roulette / Unlabeled Assertions | `lab4/test_snake_rules.cpp:115` | Add custom failure messages (`EXPECT_EQ(...) << "Failed on move step"`) or split into separate sub-tests. |
