#include "Game.h"

#include <iostream>
#include <memory>
#include <vector>

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/mat4x4.hpp"
#include "GLFW/glfw3.h"

#include "Game.h"
#include "../Resources/ResourceManager.h"
#include "../Render/AnimatedSprite.h"
#include "../Render/ShaderProgram.h"
#include "Tank.h"

namespace Render {
    class AnimatedSprite;
    class Sprite;
    class ShaderProgram;
    class Texture2D;
}

namespace GameEngine {
    Game::Game(const glm::ivec2& WindowSize) : m_eCurrentGameState(EGameState::Active),
                                               m_WindowSize(WindowSize) {
        m_keys.fill(false);
    }

    Game::~Game() {

    }

    void Game::render() {
        // ResourceManager::getAnimatedSprite("DefaultAnimatedSprite")->render();

        if (m_pTank) {
            m_pTank->render();
        }

    }

    void Game::update(const uint64_t delta) {
        // ResourceManager::getAnimatedSprite("DefaultAnimatedSprite")->update(delta);

        if (m_pTank) {
            if (m_keys[GLFW_KEY_W]) {
                m_pTank->setOrientation(Tank::EOrientation::Top);
                m_pTank->move(true);
            }
            else if (m_keys[GLFW_KEY_A]) {
                m_pTank->setOrientation(Tank::EOrientation::Left);
                m_pTank->move(true);
            }
            else if (m_keys[GLFW_KEY_D]) {
                m_pTank->setOrientation(Tank::EOrientation::Right);
                m_pTank->move(true);
            }
            else if (m_keys[GLFW_KEY_S]) {
                m_pTank->setOrientation(Tank::EOrientation::Bottom);
                m_pTank->move(true);
            }
            else {
                m_pTank->move(false);
            }

            m_pTank->update(delta);
        }

    }

    void Game::setKey(const int key, const int action) {
        m_keys[key] = action;
    }

    bool Game::init() {

        std::shared_ptr<Render::ShaderProgram> p_ShaderProgram = ResourceManager::loadShaderProgram(
            "TriangleShader", "res/Shaders/vertex_shader.txt", "res/Shaders/fragment_shader.txt");

        if (!p_ShaderProgram) {
            std::cerr << "ERROR WHILE LOADING SHADER PROGRAM" << std::endl;
            return false;
        }

        std::shared_ptr<Render::ShaderProgram> p_SpriteShaderProgram = ResourceManager::loadShaderProgram(
    "SpritesShader", "res/Shaders/vSprite.txt", "res/Shaders/fSprite.txt");

        if (!p_SpriteShaderProgram) {
            std::cerr << "ERROR WHILE LOADING SHADER PROGRAM" << std::endl;
            return false;
        }

        std::shared_ptr<Render::Texture2D> texture = ResourceManager::loadTexture("DefaultTexture", "res\\Textures\\map_8x8.png");

        std::vector<std::string> subTexturesNames = {
            "Bird",
            "Flag",
            "Star_1",
            "Star_2",
            "Star_3",
            "Star_4",
            "Cross_1",
            "Cross_2",
            "BigBoom_1_1",
            "BigBoom_1_2",
            "BigBoom_2_1",
            "BigBoom_2_2",
            "Boom_1",
            "Boom_2",
            "Boom_3",
        };
        std::shared_ptr<Render::Texture2D> pTextureAtlas = ResourceManager::loadTextuteAtlas("DefaultTextureAtlas", "res\\Textures\\map_16x16.png", std::move(subTexturesNames), 16, 16);

        std::shared_ptr<Render::AnimatedSprite> p_animatedSprite = ResourceManager::loadAnimatedSprite("DefaultAnimatedSprite", "DefaultTextureAtlas", "SpritesShader", "Flag", 100, 100);

        std::vector<std::pair<std::string, uint64_t>> birdStates;
        birdStates.emplace_back(std::make_pair(std::string("Bird"), 1000000000));
        birdStates.emplace_back(std::make_pair(std::string("Flag"), 1000000000));

        std::vector<std::pair<std::string, uint64_t>> boomStates;
        boomStates.emplace_back(std::make_pair(std::string("Boom_1"), 1000000000));
        boomStates.emplace_back(std::make_pair(std::string("Boom_2"), 1000000000));
        boomStates.emplace_back(std::make_pair(std::string("Boom_3"), 1000000000));

        p_animatedSprite->insertState(std::string("Bird"), std::move(birdStates));
        p_animatedSprite->insertState(std::string("Boom"), std::move(boomStates));

        p_animatedSprite->setState("Boom");

        p_animatedSprite->setPosition(glm::vec2(270.0f, 190.0f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_WindowSize.x), 0.f,
                                                 static_cast<float>(m_WindowSize.y), -100.f, 100.f);

        p_SpriteShaderProgram->use();
        p_SpriteShaderProgram->setMatrix4("projectionMatrix", projectionMatrix);
        p_SpriteShaderProgram->setInt("tex", GL_TEXTURE0);

        std::vector<std::string> tanksSubTexturesNames = {
            "TankTop_1",
            "TankTop_2",
            "TankLeft_1",
            "TankLeft_2",
            "TankBottom_1",
            "TankBottom_2",
            "TankRight_1",
            "TankRight_2",
        };

        auto pTextureTanksAtlas = ResourceManager::loadTextuteAtlas("TanksTextureAtlas", "res\\Textures\\tanks.png", std::move(tanksSubTexturesNames), 16, 16);
        auto pTanksAnimatedSprite = ResourceManager::loadAnimatedSprite("TankAnimatedSprite", "TanksTextureAtlas", "SpritesShader", "TankTop_1", 100, 100);

        std::vector<std::pair<std::string, uint64_t>> tankTopStates;
        tankTopStates.emplace_back(std::make_pair(std::string("TankTop_1"), 500000000));
        tankTopStates.emplace_back(std::make_pair(std::string("TankTop_2"), 500000000));

        std::vector<std::pair<std::string, uint64_t>> tankBottomStates;
        tankBottomStates.emplace_back(std::make_pair(std::string("TankBottom_1"), 500000000));
        tankBottomStates.emplace_back(std::make_pair(std::string("TankBottom_2"), 500000000));

        std::vector<std::pair<std::string, uint64_t>> tankLeftStates;
        tankLeftStates.emplace_back(std::make_pair(std::string("TankLeft_1"), 500000000));
        tankLeftStates.emplace_back(std::make_pair(std::string("TankLeft_2"), 500000000));

        std::vector<std::pair<std::string, uint64_t>> tankRightStates;
        tankRightStates.emplace_back(std::make_pair(std::string("TankRight_1"), 500000000));
        tankRightStates.emplace_back(std::make_pair(std::string("TankRight_2"), 500000000));

        pTanksAnimatedSprite->insertState(std::string("tankTopState"),    std::move(tankTopStates));
        pTanksAnimatedSprite->insertState(std::string("tankBottomState"), std::move(tankBottomStates));
        pTanksAnimatedSprite->insertState(std::string("tankLeftState"),   std::move(tankLeftStates));
        pTanksAnimatedSprite->insertState(std::string("tankRightState"),  std::move(tankRightStates));

        pTanksAnimatedSprite->setState("tankTopState");

        m_pTank = std::make_unique<Tank>(pTanksAnimatedSprite, 0.0000001f, glm::vec2(100, 100));

        return true;
    }

    glm::ivec2 Game::getWindowSize() const {
        return m_WindowSize;
    }
}
