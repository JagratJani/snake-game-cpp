#include "Game.h"
#include <cstdlib>
#include <ctime>

namespace {
    class RandomInitializer {
    public:
        RandomInitializer() {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            for (int i = 0; i < 10; i++) {
                std::rand();
            }
        }
    };
    
    RandomInitializer randomInit;
}

int main() {
    Game game;
    game.Run();
    return 0;
}