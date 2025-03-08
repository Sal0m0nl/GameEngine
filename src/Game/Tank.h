#pragma once

#include <memory>

#include "glm/vec2.hpp"

namespace Render {
    class AnimatedSprite;
}

namespace GameEngine {

    class Tank {

    public:

        enum class EOrientation {
            Top,
            Bottom,
            Left,
            Right
        };

        Tank(std::shared_ptr<Render::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);

        void render() const;
        void update(const uint64_t delta);
        void setOrientation(const EOrientation eOrientation);
        void move(const bool move);

    private:
        EOrientation m_eOrientation;
        std::shared_ptr<Render::AnimatedSprite> m_pSprite;
        bool m_move;
        float m_velocity;
        glm::vec2 m_position;
        glm::vec2 m_moveOffset;
    };

}

