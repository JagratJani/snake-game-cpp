// lab4/test_seam_rand.cpp
// Part D — Commit 2: Test that exploits the rand-injection seam in Food.
//
// Rule tested: "Food is never placed on the snake's body after eating."
//
// Before the seam (Commit 1), Food::GenerateWithObstacles called rand()
// directly — there was no way to control where the food landed in a unit test.
// After the seam, Food::randSource can be replaced with any int(*)() function,
// letting us deterministically force collision attempts and verify the retry loop.
//
// Double kind: STUB — the injected function is asked a question (its return
// value is read by production code to compute food coordinates). It returns
// a pre-programmed value instead of calling std::rand.
//
// Build: use Makefile target 'partd'

#include "gtest/gtest.h"
#include "../src/Snake.h"
#include "../src/Food.h"
#include <vector>
#include <utility>

// ─── Stub rand function ───────────────────────────────────────────────────────
// We need to return the snake-head position first (to provoke a retry),
// then a safe position (off the snake).
//
// Snake(30,20) starts with head at (15,10).
// food.GenerateWithObstacles calls: x = randSource() % maxX; y = randSource() % maxY
// So the sequence of calls is: call1 → x, call2 → y, call3 → x, call4 → y, ...
//
// To hit the head: call1=15 (15%30=15), call2=10 (10%20=10) → collision.
// Safe position:   call3=1,  call4=1  → (1,1), safe.

static int s_call_count = 0;
static int stub_rand_for_head_collision() {
    s_call_count++;
    switch (s_call_count) {
        case 1: return 15;  // x = 15%30 = 15 → head X
        case 2: return 10;  // y = 10%20 = 10 → head Y (collision!)
        case 3: return 1;   // x = 1%30 = 1  → safe
        case 4: return 1;   // y = 1%20 = 1  → safe
        default: return 1;
    }
}

TEST(Rule3_FoodSeam, FoodIsNotPlacedOnSnakeHeadAfterCollisionRetry) {
    Snake snake(30, 20);
    // Head is at (15,10) by construction
    ASSERT_EQ(snake.GetHeadX(), 15);
    ASSERT_EQ(snake.GetHeadY(), 10);

    // Install stub
    Food::randSource = stub_rand_for_head_collision;
    s_call_count = 0;

    Food food(30, 20);
    food.GenerateWithObstacles(snake, {});

    // Restore real rand
    Food::randSource = std::rand;

    // Food must NOT be on the snake's head
    EXPECT_FALSE(food.GetX() == snake.GetHeadX() && food.GetY() == snake.GetHeadY());

    // Food must be at the safe position (1,1) after retry
    EXPECT_EQ(food.GetX(), 1);
    EXPECT_EQ(food.GetY(), 1);

    // The stub was called at least 4 times (2 collision, 2 safe)
    EXPECT_GE(s_call_count, 4);
}

TEST(Rule3_FoodSeam, FoodIsActiveAfterGeneration) {
    Snake snake(30, 20);
    Food::randSource = stub_rand_for_head_collision;
    s_call_count = 0;

    Food food(30, 20);
    food.GenerateWithObstacles(snake, {});
    Food::randSource = std::rand;

    EXPECT_TRUE(food.IsActive());
}

TEST(Rule3_FoodSeam, FoodNotOnBodySegment) {
    // Grow snake so it has a body segment at (14,10), (13,10)
    Snake snake(30, 20);
    // body[1] is at (14,10), body[2] at (13,10)

    // Stub: first attempt lands on body[1]=(14,10), then safe=(5,5)
    static int call_idx = 0;
    call_idx = 0;
    Food::randSource = []() -> int {
        call_idx++;
        switch (call_idx) {
            case 1: return 14; // x=14 → body segment x
            case 2: return 10; // y=10 → body segment y (collision with body[1])
            case 3: return 5;  // safe x
            case 4: return 5;  // safe y
            default: return 5;
        }
    };

    Food food(30, 20);
    food.GenerateWithObstacles(snake, {});
    Food::randSource = std::rand;

    // Food must not be on (14,10)
    EXPECT_FALSE(food.GetX() == 14 && food.GetY() == 10);
    EXPECT_EQ(food.GetX(), 5);
    EXPECT_EQ(food.GetY(), 5);
}
