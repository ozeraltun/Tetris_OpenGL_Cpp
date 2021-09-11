#ifndef SQUAREMAP_H
#define SQUAREMAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "resource_manager.h"
#include "tetris_block.h"

#include <tuple>
#include <vector>


class SquareMap
{
public:

    glm::vec2   Position, Size;
    glm::vec3   Color;
    float       Rotation;
    //initialize 10,10 array with zeros
    std::vector<std::vector<int>> values = { {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0},
                                             {0,0,0,0,0,0,0,0,0,0} };

    // render state
    Texture2D   Sprite;
    // constructor(s)
    SquareMap();
    SquareMap(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);

    virtual void collapseBlock(std::vector< std::tuple <int, int> > collapse_values);
    virtual std::vector<std::vector<int>> getValues();
    virtual void checkLines(int& score);

    virtual void resetVals();
};

#endif