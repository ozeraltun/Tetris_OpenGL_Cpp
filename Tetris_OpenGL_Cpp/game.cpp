#include <time.h>
#include <sstream>
#include <string> 

#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "tetris_enums.h"
#include "text_renderer.h"

// Game-related State data
SpriteRenderer* Renderer;
SquareMap* Squares;
TetrisBlock* Block;
TextRenderer* Text;
TetrisBlock* NextBlock;

int score = 0;
blockType random_type_next = static_cast<blockType>(rand() % Tshaped);
bool endGame = false;

Game::Game(unsigned int width, unsigned int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete Squares;
    delete Block;
    delete Text;
    delete NextBlock;
}

void Game::Init()
{
    this->gameSpeed = 1.0f;
    Text = new TextRenderer(400.0f, 500.0f);
    Text->Load("fonts/ocraext.TTF", 24);

    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("shaders/particle.vs", "shaders/particle.frag", nullptr, "particle");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    // load textures
    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/block.png", false, "tetris_block");
    ResourceManager::LoadTexture("textures/square.png", true, "square");

    srand(std::time(NULL));
    Squares = new SquareMap(glm::vec2(0.0f, 0.0f), glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("square"), glm::vec3(1.0f, 1.0f, 1.0f));
    blockType random_type = static_cast<blockType>(rand() % Tshaped);
    Block = new TetrisBlock(glm::vec2(0.0f, 0.0f), true, Up_rotation, glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), 3, 3, random_type, glm::vec3(1.0f, 1.0f, 0.0f));
    NextBlock = new TetrisBlock(glm::vec2(0.0f, 0.0f), true, Up_rotation, glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), 12, 3, random_type_next, glm::vec3(1.0f, 1.0f, 0.0f));
}

void Game::Update()
{

    if (endGame) {
        return;
    }
    if (Block->checkDownAvail(Squares->getValues())) {
        Block->downUpdate();
    }

    else {
        std::cout << "BLOCK COLLAPSE SIGNAL INSIDE GAME" << std::endl;
        Squares->collapseBlock(Block->getCollapseVals());
        Squares->checkLines(score);

        Block = new TetrisBlock(glm::vec2(0.0f, 0.0f), true, Up_rotation, glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), 3, 3, random_type_next, glm::vec3(1.0f, 1.0f, 0.0f));
        Block->checkFinish(Squares->getValues(), endGame);
        if (endGame) {
            std::cout << "Game has ended" << std::endl;
            this->State = GAME_END;
            return;
        }
        this->gameSpeed = 1.0f - (score / 10) * 0.02;
        random_type_next = static_cast<blockType>(rand() % Tshaped);
        NextBlock = new TetrisBlock(glm::vec2(0.0f, 0.0f), true, Up_rotation, glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), 12, 3, random_type_next, glm::vec3(1.0f, 1.0f, 0.0f));

    }
}

float Game::getTimeUpdate() {
    return this->gameSpeed;
}
void Game::ProcessInput()
{
    if (this->State == GAME_ACTIVE) {
        if (Block->Alive) {
            if (this->Keys[GLFW_KEY_UP]) {
                if (checkBoundariesRotation()) {
                    Block->changeRotation();
                }
            }
            if (this->Keys[GLFW_KEY_RIGHT]) {
                if (checkBoundariesMovement(Right_movement)) {
                    Block->changePosRight();
                }
            }
            if (this->Keys[GLFW_KEY_LEFT]) {
                if (checkBoundariesMovement(Left_movement)) {
                    Block->changePosLeft();
                }
            }
        }

    }

}
void Game::resetGame() {
    Squares->resetVals();
    score = 0;
    resetBlocks();
    this->State = GAME_ACTIVE;
    endGame = false;
    this->gameSpeed = 1.0f;
}
void Game::resetBlocks() {
    blockType random_type = static_cast<blockType>(rand() % Tshaped);
    Block = new TetrisBlock(glm::vec2(0.0f, 0.0f), true, Up_rotation, glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), 3, 3, random_type, glm::vec3(1.0f, 1.0f, 0.0f));
    random_type_next = static_cast<blockType>(rand() % Tshaped);
    NextBlock = new TetrisBlock(glm::vec2(0.0f, 0.0f), true, Up_rotation, glm::vec2(40.0f, 40.0f), ResourceManager::GetTexture("block"), 12, 3, random_type_next, glm::vec3(1.0f, 1.0f, 0.0f));
}
bool Game::checkBoundariesRotation() {
    bool availability = Block->checkRotationAvail(Squares->getValues());
    return availability;
}
bool Game::checkBoundariesMovement(movementType moveType) {
    bool availability = Block->checkMovementAvail(Squares->getValues(), moveType);
    return availability;

}
void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        // draw background
        Texture2D background_Texture = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(background_Texture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

        //Draw Objects
        Squares->Draw(*Renderer);
        Block->Draw(*Renderer);
        NextBlock->Draw(*Renderer);


        std::string score_str = std::to_string(score);
        Text->RenderText("Made by Ozer Altun", 10.0f, 473.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
        Text->RenderText("SCORE:", 320.0f, 180.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
        Text->RenderText(score_str, 320.0f, 210.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
        Text->RenderText("NEXT:", 320.0f, 5.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));

    }
    if (this->State == GAME_MENU) {
        Text->RenderText("Press ENTER to start", 250.0f, this->Height / 2.0f, 1.0f);
        Text->RenderText("Press W or S to select level", 245.0f, this->Height / 2.0f + 20.0f, 0.75f);
    }
    if (this->State == GAME_END) {
        std::string score_str = std::to_string(score);
        Text->RenderText("GAME ENDED WITH SCORE " + score_str, 0.0f, 80.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
        Text->RenderText("Press R for restart ", 0.0f, 150.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
}




void Game::setPause(bool updatable) {
    if (updatable) {
        //std::cout << "updatable is true" << std::endl;
    }
    else {
        //std::cout << "updatable is false" << std::endl;
        Text->RenderText("Press SPACE to continue", 20.0f, 20.0f, 1.0f, glm::vec3(1.0f, 0.3f, 0.0f));

    }
}
