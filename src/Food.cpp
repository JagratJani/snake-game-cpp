#include "Food.h"
#include <cstdlib>
#include <ctime>

// Initialize random seed only once
namespace {
    bool randomInitialized = false;
    void InitializeRandom() {
        if (!randomInitialized) {
            srand(static_cast<unsigned int>(time(nullptr)));
            randomInitialized = true;
        }
    }
}

Food::Food(int width, int height) : maxX(width), maxY(height) {
    // Don't initialize random here - lazy initialization
}

void Food::Generate(const Snake& snake) {
    // Initialize random only when first needed
    if (!randomInitialized) {
        InitializeRandom();
    }
    
    bool onSnake;
    
    do {
        onSnake = false;
        x = rand() % maxX;
        y = rand() % maxY;
        
        if (x == snake.GetHeadX() && y == snake.GetHeadY()) {
            onSnake = true;
            continue;
        }
        
        if (snake.IsBody(x, y)) {
            onSnake = true;
        }
        
    } while (onSnake);
}