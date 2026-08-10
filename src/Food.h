#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"
#include <vector>
#include <utility>

class Food {
public:
    enum FoodType { 
        REGULAR,    // Normal food +10 points
        GOLDEN      // Special food +30 points
    };

private:
    int x, y;
    int maxX, maxY;
    FoodType type;
    bool active;

public:
    Food(int width, int height);
    void Generate(const Snake& snake, const Snake& snake2);
    void GenerateWithObstacles(const Snake& snake, const Snake& snake2, const std::vector<std::pair<int, int>>& obstacles);
    void GenerateSpecialFood(const Snake& snake, const Snake& snake2);
    
    // Getters
    int GetX() const { return x; }
    int GetY() const { return y; }
    FoodType GetType() const { return type; }
    bool IsActive() const { return active; }
    void SetActive(bool state) { active = state; }

    // Effect methods
    int GetPoints() const;
    
    // Visual representation
    char GetDisplayChar() const;
    int GetColor() const;
};

#endif