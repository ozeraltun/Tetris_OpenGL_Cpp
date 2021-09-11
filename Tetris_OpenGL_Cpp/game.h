#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "tetris_block.h"
#include "square_map.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_END
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};


class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width, Height;

    float gameSpeed;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput();
    void Update();
    void Render();

    void ResetLevel();
    void ResetPlayer();


    void setPause(bool updatable);

    bool checkBoundariesRotation();
    bool checkBoundariesMovement(movementType moveType);

    void resetGame();
    void resetBlocks();

    float getTimeUpdate();
};

#endif