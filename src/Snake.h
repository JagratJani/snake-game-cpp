#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Segment {
    int x, y;
};

class Snake {
private:
    std::vector<Segment> body;
    Direction dir;
    int maxX, maxY;
    bool grown;
    
public:
    Snake(int width, int height, int startX = -1, int startY = -1);
    
    void ChangeDirection(Direction newDir);
    void Move();
    void Grow();
    bool CheckSelfCollision() const;
    bool IsBody(int x, int y) const;
    
    // Getters
    int GetHeadX() const { return body[0].x; }
    int GetHeadY() const { return body[0].y; }
    Direction GetDirection() const { return dir; }
    const std::vector<Segment>& GetBody() const { return body; }
};

#endif