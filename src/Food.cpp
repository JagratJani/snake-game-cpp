#include "Food.h"
#include <cstdlib>
#include <ctime>

// Initialize random seed only once

Food::Food(int width, int height) : maxX(width), maxY(height), type(REGULAR), active(false) {
    // Don't initialize random here - lazy initialization
}

void Food::Generate(const Snake& snake, const Snake& snake2) {
   
    
    // Default to regular food
    GenerateWithObstacles(snake, snake2, std::vector<std::pair<int, int>>());
}

void Food::GenerateWithObstacles(const Snake& snake, const Snake& snake2, const std::vector<std::pair<int, int>>& obstacles) {
    
    
    // Default to regular food
    type = REGULAR;
    
    bool invalidPosition;
    
    do {
        invalidPosition = false;
        x = rand() % maxX;
        y = rand() % maxY;
        
        // Check if position is on snake head
        if ((x == snake.GetHeadX() && y == snake.GetHeadY()) ||
            (x == snake2.GetHeadX() && y == snake2.GetHeadY())) {
            invalidPosition = true;
            continue;
        }
        
        // Check if position is on snake body
        if (snake.IsBody(x, y) || snake2.IsBody(x, y)) {
            invalidPosition = true;
            continue;
        }
        
        // Check if position is on any obstacle
        for (const auto& obstacle : obstacles) {
            if (x == obstacle.first && y == obstacle.second) {
                invalidPosition = true;
                break;
            }
        }
        
    } while (invalidPosition);
    
    active = true;
}

void Food::GenerateSpecialFood(const Snake& snake, const Snake& snake2) {
   
    
    // Generate position first (same logic as regular food)
    bool invalidPosition;
    
    do {
        invalidPosition = false;
        x = rand() % maxX;
        y = rand() % maxY;
        
        if ((x == snake.GetHeadX() && y == snake.GetHeadY()) ||
            (x == snake2.GetHeadX() && y == snake2.GetHeadY())) {
            invalidPosition = true;
            continue;
        }
        
        if (snake.IsBody(x, y) || snake2.IsBody(x, y)) {
            invalidPosition = true;
            continue;
        }
        
    } while (invalidPosition);
    
    // Set as golden food
    type = GOLDEN;
    active = true;
}

int Food::GetPoints() const {
    switch (type) {
        case REGULAR: return 10;
        case GOLDEN: return 30;  // Extra points for golden food
        default: return 10;
    }
}

char Food::GetDisplayChar() const {
    switch (type) {
        case REGULAR: return '\xDB';  // Same block character we were using for regular food
        case GOLDEN: return '@';      // @ symbol for special food
        default: return '\xDB';
    }
}

int Food::GetColor() const {
    switch (type) {
        case REGULAR: return 12; // Bright Red (same as before)
        case GOLDEN: return 14;  // Bright Yellow for golden food
        default: return 12;
    }
}