#include "square_map.h"

SquareMap::SquareMap()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Color(1.0f), Rotation(0.0f), Sprite() { }

SquareMap::SquareMap(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
    : Position(pos), Size(size), Color(color), Rotation(0.0f), Sprite(sprite) { }

void SquareMap::Draw(SpriteRenderer& renderer)
{
    unsigned int position_inc_x = 0;
    unsigned int position_inc_y = 0;

    glm::vec2   PositionOffset = this->Position;
    for (unsigned int row = 0; row < 10; row++) {
        for (unsigned int col = 0; col < 20; col++) {
            position_inc_x = row * 40.0f;
            position_inc_y = col * 40.0f;
            glm::vec2 Position_written = glm::vec2(position_inc_x, PositionOffset.y + position_inc_y);
            renderer.DrawSprite(this->Sprite, Position_written, this->Size, this->Rotation, this->Color);
        }
    }

    position_inc_x = 0;
    position_inc_y = 0;
    Texture2D fillerSprite = ResourceManager::GetTexture("block");
    for (unsigned int row = 0; row < 10; row++) {
        for (unsigned int col = 0; col < 20; col++) {
            position_inc_x = row * 40.0f;
            position_inc_y = col * 40.0f;
            glm::vec2 Position_written = glm::vec2(position_inc_x, PositionOffset.y + position_inc_y);
            if (this->values[col][row] == 1) {
                renderer.DrawSprite(fillerSprite, Position_written, this->Size, this->Rotation, this->Color);
            }
        }
    }

}

void SquareMap::collapseBlock(std::vector< std::tuple <int, int> > collapse_values) {
    for (int i = 0; i < 4; i++) {
        int x_val = std::get<0>(collapse_values[i]);
        int y_val = std::get<1>(collapse_values[i]);
        values[y_val][x_val] = 1;
    }
}

std::vector<std::vector<int>> SquareMap::getValues() {
    return this->values;
}

void SquareMap::checkLines(int& score) {
    std::vector<int> lineNumbersCompleted;
    for (int col = 0; col < 20; col++) {
        bool colIsFull = true;
        for (int row = 0; row < 10; row++) {
            if (this->values[col][row] == 0) {
                colIsFull = false;
            }
        }
        if (colIsFull) {
            lineNumbersCompleted.push_back(col);
        }
    }

    score = score + lineNumbersCompleted.size() * 10;
    for (int col_delete_index = 0; col_delete_index < lineNumbersCompleted.size(); col_delete_index++) {
        //delete row lineNumbersCompleted[col_delete_index];
        std::cout << "we should delete col : " << lineNumbersCompleted[col_delete_index] << std::endl;

        for (int row = 0; row < 10; row++) {
            this->values[lineNumbersCompleted[col_delete_index]][row] = 0;

        }

        //all the things upside this must get lower:
        for (int col = lineNumbersCompleted[col_delete_index]; col > 0; col--) {
            this->values[col] = this->values[col - 1];
        }
    }

}

void SquareMap::resetVals() {
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 20; col++) {
            this->values[col][row] = 0;
        }
    }
}