#pragma once

#include <array>
#include <cstdint>

#include "glm/vec2.hpp"

namespace GameEngine {
    class Game {

    public:
        Game(const glm::ivec2& WindowSize);
        ~Game();

        void render();
        void update(const uint64_t delta);
        void setKey(const int key, const int action);
        bool init();
        glm::ivec2 getWindowSize() const;

    private:
        std::array<bool, 349> m_keys;

        enum class EGameState {
            Active,
            Pause
        };

        EGameState m_eCurrentGameState;

        glm::ivec2 m_WindowSize;
    };
}

