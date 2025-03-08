#include "Tank.h"

#include "../Render/AnimatedSprite.h"

namespace GameEngine {

    Tank::Tank(std::shared_ptr<Render::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position) : m_eOrientation(EOrientation::Top),
                                                                                                             m_pSprite(pSprite),
                                                                                                             m_move(false),
                                                                                                             m_velocity(velocity),
                                                                                                             m_position(position),
                                                                                                             m_moveOffset(glm::vec2(0.f, 1.f))
    {
        m_pSprite->setPosition(m_position);
    }

    void Tank::render() const {
        m_pSprite->render();
    }

    void Tank::update(const uint64_t delta) {
        if (m_move) {
            m_pSprite->update(delta);
            m_position += delta * m_velocity * m_moveOffset;
            m_pSprite->setPosition(m_position);
        }
    }

    void Tank::setOrientation(const EOrientation eOrientation) {
        if (m_eOrientation == eOrientation)
            return;

        m_eOrientation = eOrientation;
        switch (eOrientation) {
        case EOrientation::Top:
            m_pSprite->setState("tankTopState");
            m_moveOffset.x = 0.f;
            m_moveOffset.y = 1.f;
            break;
        case EOrientation::Bottom:
            m_pSprite->setState("tankBottomState");
            m_moveOffset.x = 0.f;
            m_moveOffset.y = -1.f;
            break;
        case EOrientation::Left:
            m_pSprite->setState("tankLeftState");
            m_moveOffset.x = -1.f;
            m_moveOffset.y = 0.f;
            break;
        case EOrientation::Right:
            m_pSprite->setState("tankRightState");
            m_moveOffset.x = 1.f;
            m_moveOffset.y = 0.f;
            break;
        default:
            break;
        }
    }

    void Tank::move(const bool move) {
        m_move = move;
    }
}

