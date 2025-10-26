#include "Snake.h"
#include <cstddef>

Snake::Snake(int width, int height) : maxX(width), maxY(height), grown(false) {
    // Initialize snake in the middle of the screen
    Segment head = { width / 2, height / 2 };
    body.push_back(head);
    
    // Add initial body segments
    for (int i = 1; i < 3; i++) {
        Segment segment = { head.x - i, head.y };
        body.push_back(segment);
    }
    
    dir = RIGHT;
}

void Snake::ChangeDirection(Direction newDir) {
    // Prevent 180-degree turns
    if ((dir == LEFT && newDir != RIGHT) ||
        (dir == RIGHT && newDir != LEFT) ||
        (dir == UP && newDir != DOWN) ||
        (dir == DOWN && newDir != UP)) {
        dir = newDir;
    }
}

void Snake::Move() {
    // Save current head position
    Segment newHead = body[0];
    
    // Move head based on direction
    switch (dir) {
        case LEFT:  newHead.x--; break;
        case RIGHT: newHead.x++; break;
        case UP:    newHead.y--; break;
        case DOWN:  newHead.y++; break;
        case STOP:  // Do nothing if stopped
            break;
    }
    
    // Insert new head
    body.insert(body.begin(), newHead);
    
    // Remove tail if not grown
    if (!grown) {
        body.pop_back();
    } else {
        grown = false;
    }
}

void Snake::Grow() {
    grown = true;
}

bool Snake::CheckSelfCollision() const {
    for (std::size_t i = 1; i < body.size(); i++) {
        if (body[0].x == body[i].x && body[0].y == body[i].y) {
            return true;
        }
    }
    return false;
}

bool Snake::IsBody(int x, int y) const {
    for (std::size_t i = 1; i < body.size(); i++) {
        if (body[i].x == x && body[i].y == y) {
            return true;
        }
    }
    return false;
}