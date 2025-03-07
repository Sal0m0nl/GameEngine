
#include <iostream>
#include <memory>
#include <vector>

#include "glad/glad.h"
#include "glm/vec2.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/mat4x4.hpp"

#include "Game.h"
#include "../Resources/ResourceManager.h"
#include "../Render/AnimatedSprite.h"
#include "../Render/ShaderProgram.h"

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
        ResourceManager::getAnimatedSprite("DefaultAnimatedSprite")->render();
    }

    void Game::update(const uint64_t delta) {
        ResourceManager::getAnimatedSprite("DefaultAnimatedSprite")->update(delta);
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

        return true;
    }

    glm::ivec2 Game::getWindowSize() const {
        return m_WindowSize;
    }
}
