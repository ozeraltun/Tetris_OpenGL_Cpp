#include "tetris_block.h"

TetrisBlock::TetrisBlock()
    : Position(0.0f, 0.0f), Alive(true), m_rotation(Up_rotation), Size(1.0f, 1.0f), Color(1.0f), Rotation(0.0f), Sprite(), pos_X(5), pos_Y(2), m_blockType(Lshaped) { }

TetrisBlock::TetrisBlock(glm::vec2 pos, bool alive, rotationType rotation, glm::vec2 size, Texture2D sprite, int pos_x, int pos_y, blockType blocktype, glm::vec3 color)
    : Position(pos), Alive(alive), m_rotation(rotation), Size(size), Color(color), Rotation(0.0f), Sprite(sprite), pos_X(pos_x), m_blockType(blocktype), pos_Y(pos_y) { }

void TetrisBlock::Draw(SpriteRenderer& renderer)
{
    BlockSequence currentSequence(this->m_blockType, this->m_rotation);
    for (int i = 0; i < 4; i++) {
        glm::vec2 drawPos = glm::vec2(this->pos_X * 40.0f + std::get<0>(currentSequence.getSequence()[i]) * 40.0f, this->pos_Y * 40.0f + std::get<1>(currentSequence.getSequence()[i]) * 40.0f);
        renderer.DrawSprite(this->Sprite, drawPos, this->Size, this->Rotation, this->Color);
    }
}


void TetrisBlock::changeRotation() {
    if (this->m_rotation == Up_rotation) {
        this->m_rotation = Right_rotation;
    }
    else if (this->m_rotation == Right_rotation) {
        this->m_rotation = Down_rotation;
    }
    else if (this->m_rotation == Down_rotation) {
        this->m_rotation = Left_rotation;
    }
    else if (this->m_rotation == Left_rotation) {
        this->m_rotation = Up_rotation;
    }
}

rotationType TetrisBlock::getNextRotation() {
    rotationType next_rotation;
    if (this->m_rotation == Up_rotation) {
        next_rotation = Right_rotation;
    }
    else if (this->m_rotation == Right_rotation) {
        next_rotation = Down_rotation;
    }
    else if (this->m_rotation == Down_rotation) {
        next_rotation = Left_rotation;
    }
    else if (this->m_rotation == Left_rotation) {
        next_rotation = Up_rotation;
    }

    return next_rotation;
}

void TetrisBlock::changePosRight() {
    if (this->checkAvail(Right_movement)) {
        this->pos_X = this->pos_X + 1;
    }

}

void TetrisBlock::changePosLeft() {
    if (this->checkAvail(Left_movement)) {
        this->pos_X = this->pos_X - 1;
    }
}

void TetrisBlock::downUpdate() {
    this->pos_Y = this->pos_Y + 1;
}


bool TetrisBlock::checkDownAvail(std::vector<std::vector<int>> mapValues) {
    const int Y_THRESHOLD = 19;
    bool availability = true;
    BlockSequence currentSequence(this->m_blockType, this->m_rotation);
    for (int i = 0; i < 4; i++) {
        if (pos_Y + std::get<1>(currentSequence.getSequence()[i]) + 1 > Y_THRESHOLD) {
            availability = false;
        }
        int searchPosX = (pos_X + std::get<0>(currentSequence.getSequence()[i]));
        int searchPosY = (pos_Y + std::get<1>(currentSequence.getSequence()[i]));
        std::cout << "x = " << searchPosX << std::endl;
        std::cout << "y = " << searchPosY << std::endl;

        //error purpose array cannot exeed range
        if (searchPosY + 1 <= 19) {
            if (mapValues[searchPosY + 1][searchPosX] == 1) {
                availability = false;
            }
        }


        /*if (mapValues[pos_X + std::get<0>(currentSequence.getSequence()[i])][pos_Y + std::get<1>(currentSequence.getSequence()[i]) + 1] == 1) {
            availability = false;
        }*/
        // std::cout << "current y value i = " << pos_Y + std::get<1>(currentSequence.getSequence()[i]) << std::endl;
    }
    return availability;
}
bool TetrisBlock::checkRotationAvail(std::vector<std::vector<int>> mapValues) {
    const int Y_THRESHOLD_HIGH = 19;
    const int Y_THRESHOLD_LOW = 0;

    const int X_THRESHOLD_HIGH = 9;
    const int X_THRESHOLD_LOW = 0;

    bool availability = true;
    BlockSequence nextSequence(this->m_blockType, getNextRotation());

    for (int i = 0; i < 4; i++) {
        if (pos_Y + std::get<1>(nextSequence.getSequence()[i]) > Y_THRESHOLD_HIGH) {
            availability = false;
            break;
        }
        else if (pos_Y + std::get<1>(nextSequence.getSequence()[i]) < Y_THRESHOLD_LOW) {
            availability = false;
            break;
        }
        else if (pos_X + std::get<0>(nextSequence.getSequence()[i]) > X_THRESHOLD_HIGH) {
            availability = false;
            break;
        }
        else if (pos_X + std::get<0>(nextSequence.getSequence()[i]) < X_THRESHOLD_LOW) {
            availability = false;
            break;
        }

        int searchPosX = (pos_X + std::get<0>(nextSequence.getSequence()[i]));
        int searchPosY = (pos_Y + std::get<1>(nextSequence.getSequence()[i]));

        if (searchPosX >= 0 && searchPosX <= 9 && searchPosY >= 0 && searchPosY <= 19) {
            if (mapValues[searchPosY][searchPosX] == 1) {
                availability = false;
                break;
            }
        }

        /*if (mapValues[pos_X + std::get<0>(currentSequence.getSequence()[i])][pos_Y + std::get<1>(currentSequence.getSequence()[i]) + 1] == 1) {
            availability = false;
        }*/
        // std::cout << "current y value i = " << pos_Y + std::get<1>(currentSequence.getSequence()[i]) << std::endl;
    }

    return availability;
}
bool TetrisBlock::checkMovementAvail(std::vector<std::vector<int>> mapValues, movementType moveType) {
    const int X_THRESHOLD_HIGH = 9;
    const int X_THRESHOLD_LOW = 0;
    bool availability = true; //one false will be enough
    BlockSequence currentSequence(this->m_blockType, this->m_rotation);



    if (moveType == Right_movement) {
        for (int i = 0; i < 4; i++) {
            int searchPosX = (pos_X + std::get<0>(currentSequence.getSequence()[i]));
            int searchPosY = (pos_Y + std::get<1>(currentSequence.getSequence()[i]));

            if (pos_X + std::get<0>(currentSequence.getSequence()[i]) + 1 > X_THRESHOLD_HIGH) {
                return false;
            }
            if (searchPosX + 1 <= 9) {
                if (mapValues[searchPosY][searchPosX + 1] == 1) {
                    return false;
                }
            }
        }
    }

    if (moveType == Left_movement) {
        for (int i = 0; i < 4; i++) {
            int searchPosX = (pos_X + std::get<0>(currentSequence.getSequence()[i]));
            int searchPosY = (pos_Y + std::get<1>(currentSequence.getSequence()[i]));

            if (pos_X + std::get<0>(currentSequence.getSequence()[i]) - 1 < X_THRESHOLD_LOW) {
                return false;
            }
            if (searchPosX - 1 >= 0) {
                if (mapValues[searchPosY][searchPosX - 1] == 1) {
                    return false;
                }
            }
        }
    }

    return availability;
}
void TetrisBlock::checkFinish(std::vector<std::vector<int>> mapValues, bool& endGame) {
    BlockSequence currentSequence(this->m_blockType, this->m_rotation);
    for (int i = 0; i < 4; i++) {
        int searchPosX = (pos_X + std::get<0>(currentSequence.getSequence()[i]));
        int searchPosY = (pos_Y + std::get<1>(currentSequence.getSequence()[i]));


        if (mapValues[searchPosY][searchPosX] == 1) {
            endGame = true;
            return;
        }
    }
}
bool TetrisBlock::checkAvail(movementType movType) {
    const int X_THRESHOLD_RIGHT = 9;
    const int X_THRESHOLD_LEFT = 0;

    bool availability = true;
    BlockSequence currentSequence(this->m_blockType, this->m_rotation);
    if (movType == Right_movement) {
        for (int i = 0; i < 4; i++) {
            if (pos_X + std::get<0>(currentSequence.getSequence()[i]) + 1 > X_THRESHOLD_RIGHT) {

                availability = false;
            }
            std::cout << "current x value i = " << pos_X + std::get<0>(currentSequence.getSequence()[i]) << std::endl;
        }
    }

    if (movType == Left_movement) {
        for (int i = 0; i < 4; i++) {
            if (pos_X + std::get<0>(currentSequence.getSequence()[i]) - 1 < X_THRESHOLD_LEFT) {
                availability = false;
            }
            std::cout << "current x value i = " << pos_X + std::get<0>(currentSequence.getSequence()[i]) << std::endl;
        }
    }

    return availability;
}

std::vector< std::tuple <int, int> > TetrisBlock::getCollapseVals() {
    std::vector< std::tuple <int, int> > collapse_values;
    BlockSequence currentSequence(this->m_blockType, this->m_rotation);
    for (int i = 0; i < 4; i++) {
        collapse_values.push_back({ pos_X + std::get<0>(currentSequence.getSequence()[i]), pos_Y + std::get<1>(currentSequence.getSequence()[i]) });
    }
    return collapse_values;
}