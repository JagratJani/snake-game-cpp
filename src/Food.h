#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"

class Food {
private:
    int x, y;
    int maxX, maxY;
    
public:
    Food(int width, int height);
    void Generate(const Snake& snake);
    
    // Getters
    int GetX() const { return x; }
    int GetY() const { return y; }
};

#endif