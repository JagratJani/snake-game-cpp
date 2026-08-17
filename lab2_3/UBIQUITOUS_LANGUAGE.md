# Ubiquitous Language

## Game Core

| Term | Definition | Aliases to avoid | In code |
| --- | --- | --- | --- |
| **Snake** | Player-controlled serpent entity composed of connected coordinate segments moving across the grid. | Player, serpent, worm | `Snake` — `src/Snake.h:12` |
| **Segment** | A discrete grid position coordinate (x, y) forming part of a snake's head or body. | Node, block, point, cell | `Segment` — `src/Snake.h:8` |
| **Direction** | The current cardinal orientation of snake movement (UP, DOWN, LEFT, RIGHT, STOP). | Heading, vector, orientation | `Direction` — `src/Snake.h:6` |
| **Food** | A consumable item generated on the board that provides score points and grows the snake when eaten. | Fruit, item, target, pellet | `Food` — `src/Food.h:8` |
| **Obstacle** | A fixed coordinate wall or barrier generated on the grid that causes game over upon collision. | Wall, block, hurdle, barrier | `obstacles` — `src/Game.h:22` |
| **Score** | The non-negative integer representing total points accumulated by a player during a single game run. | Points, tally, count | `score` — `src/Game.h:23` |
| **HighScore** | The top historical scores recorded persistently in disk storage across game sessions. | Leaderboard, top score, record | `HighScore` — `src/HighScore.h:12` |
| **Game** | The central controller managing state transitions, board grid, render loop, collision logic, and user input. | Engine, manager, controller | `Game` — `src/Game.h:12` |

## Relationships

- A **Game** contains exactly one **Snake**, one active **Food**, and zero or more **Obstacles**.
- A **Snake** contains one or more **Segments** (one head segment at index 0 and zero or more body segments).
- A **Food** has a position $(x, y)$ and a type (`REGULAR` or `GOLDEN`).
- A **Game** updates **Score** when a **Snake**'s head occupies the same grid coordinates as active **Food**.

## Example dialogue

> **Dev:** "When the **Snake** moves, do we check for **Food** collision before or after checking for **Obstacle** collision?"
>
> **Domain expert:** "After the **Snake** advances its head **Segment**, check if it collided with a wall or an **Obstacle** first. If it survived, check if the head position matches the active **Food**."
>
> **Dev:** "And if it hits **Food**, does the **Snake** grow immediately?"
>
> **Domain expert:** "Yes, the **Score** increases and the **Snake** gains a new **Segment** on that tick."

## Flagged ambiguities

- "Food" vs "Fruit": The assignment prompt and documentation refer to "fruit", but the codebase exclusively names the class `Food` and the variable `food`.
- "Obstacle" vs "Wall": The outer boundary border and internal obstacles use similar visual representations in `Game::Draw()`, but obstacles are generated dynamically per game run while the boundary is fixed by dimensions (`WIDTH`, `HEIGHT`).

## Code drift

| Canonical term | Called in code | Location | Note |
| --- | --- | --- | --- |
| **Fruit** | `Food` | `src/Food.h:8` | Assignment prose calls it "fruit"; codebase names it `Food`. |
| **Player** | `Snake` | `src/Game.h:17` | The single-player architecture implicitly equates the human player with the single `snake` instance. |
