# Lab 2_3 — Group A14

---

## 1. Tool and install route — [3]

| | |
|---|---|
| Agent used for run 2 | Gemini 3.6 Flash (High) via Antigravity Agent |
| `ubiquitous-language` install route | pasted `SKILL.md` (loaded from course repository `skills/ubiquitous-language/SKILL.md`) |
| `refactoring/` pack install route | pasted `SKILL.md` (loaded from course repository `skills/refactoring/review-accuracy-calibration/SKILL.md` & `skills/refactoring/detect-code-smells/SKILL.md`) |

All skills were loaded directly from the course repository definitions.

---

## 2. What I changed in the glossary — [4]

The generated file is at `lab2_3/UBIQUITOUS_LANGUAGE.md`.
- Corrected `Food` vs `Fruit` terminology drift: the assignment prose refers to "fruit", but the codebase exclusively uses `Food`.
- Explicitly distinguished `Obstacle` (dynamic spatial obstacles) from border walls (`WIDTH`, `HEIGHT`).
- Verified all terms and definitions against exact source citations (`src/Snake.h:12`, `src/Food.h:8`, `src/Game.h:12`).
- Removed generic programming terms to focus purely on domain entities and relationships.

---

## 3. Smell delta — [6]

Reports: `lab2_3/audits/main.md` (the code as received) and `lab2_3/audits/lab1-head.md` (after Lab-1 PR).

| | count | representative site (`file:line`) |
|---|---|---|
| Smells my Lab-1 PR **introduced** | 4 | `src/Game.cpp:455` |
| Smells my Lab-1 PR **left untouched** | 3 | `src/Game.h:12` |
| Smells my Lab-1 PR **removed** | 0 | — |

---

## 4. Rejected candidates — [6]

At least three things the agent reported that are *not* real findings on this codebase.

| smell reported | `file:line` | why it does not hold |
|---|---|---|
| Lazy Class | `src/Soundmanager.h:6` | Small class (15 lines), but cleanly isolates Windows API `Beep()` sound calls away from `Game` logic. |
| Data Class | `src/Snake.h:8` | `Segment` is a lightweight POD struct (`int x, y`) representing grid coordinates inside `vector<Segment>`. |
| Feature Envy | `src/Food.cpp:31` | `Food::GenerateWithObstacles` checks snake head/body coordinates to prevent spawning food on the snake, which is essential validation logic. |

---

## 5. Commit map — [7]

| # | sha | subject | what it is |
|---|---|---|---|
| 1 | bbefe32 | lab2_3: add ubiquitous language | glossary |
| 2 | 8d50a30 | lab2_3: add code smell audit | smell report |
| 3 | c2848a4 | lab2_3: refactor snake count design | **the refactor, alone** |
| 4 | 7c509fb | lab2_3: add second player | **the feature, alone** |

---

## 6. Two-run measurement — [4]

Run 1 is Lab-1 branch. Run 2 is commit 4 alone.

| | Run 1 (Lab 1) | Run 2 (commit 4) |
|---|---|---|
| Smells introduced | 4 | 0 |
| Lines changed, `git diff --shortstat -w` | 124 insertions(+), 94 deletions(-) | 60 insertions(+), 46 deletions(-) |
| Lines changed, **raw** (no `-w`) | 124 insertions(+), 94 deletions(-) | 71 insertions(+), 57 deletions(-) |
| Functions reached | 9 | 5 |
| Prompts to working code | 4 | 1 |
| Wall-clock time | 1.5 hours | 0.3 hours |

Commit 3 (the refactor) on its own: `188 insertions(+), 384 deletions(-)` -w, `231 insertions(+), 427 deletions(-)` raw.

---

## 7. Analysis Q1–Q2 — [5]

**Q1. Which smell did commit 3 actually fix?** Name it from your section 3 report. What was expensive before, what does it cost now.

Commit 3 fixed the **Divergent Change / Hardcoded Snake Count** smell at `src/Game.h:12`. Before Commit 3, adding another snake required shotgun edits across `Game` fields, constructor, `Reset()`, `Input()`, `Logic()`, `Draw()`, and `Food::GenerateWithObstacles()` because single-snake assumptions were hardcoded everywhere. Now, player state is encapsulated in `std::vector<Snake>` and `std::vector<int> scores`. All game loop methods automatically iterate over active snakes, making adding a second snake cost only initializing Player 2 in the vector and mapping WASD controls.

**Q2. Compare commit 4 to your Lab-1 diff.** Same feature, same codebase. What changed in the cost and what did not? If it got worse, say so and explain — that marks the same.

In Run 1 (Lab 1), adding the second player required touching 9 functions across 4 files (124 insertions, 94 deletions) because movement loops, collision checks, rendering, and food generation had to be manually duplicated for `snake2`. In Run 2 (Commit 4), the feature touch cost dropped to 1 file (`Game.cpp`) and 61 insertions / 38 deletions (`-w`), because `Logic()`, `Draw()`, and `Food` collision handling already processed all snakes in the `snakes` vector. The cost of key input mapping and loss display remained unchanged.

---

## 8. Analysis Q3–Q4 — [5]

**Q3. Go back through your Lab-1 `LLM-LOG.md`. Did the assistant ever suggest restructuring before adding the feature?** Quote it if it did. If it did not, what would have had to be different in your prompt?

The assistant did not suggest restructuring before adding the feature in Lab 1. In Lab 1, the prompt asked to "implement local 2-player multiplayer with minimal diff," so the assistant immediately added `snake2` and `score2` alongside `snake`. To get the assistant to restructure first, the prompt would have needed to explicitly ask: "Audit the codebase for single-player hardcoding, refactor snake representation into a collection first, and then add the second player in a separate step."

**Q4. How do you know commit 3 did not change behaviour?** Answer honestly. Most of you will find that you do not know. Say that plainly if it is true, and describe what you would have needed in order to actually know.

We do not know with complete formal certainty because this repository has no automated unit or integration test suite. We verified behavior preservation through manual execution of `snake.exe` for single-player movement, wall/obstacle collision, food growth, and scoring. To actually know with certainty, we would have needed an automated regression test suite covering input handling, collision boundaries, and game state transitions before performing Commit 3.

---
