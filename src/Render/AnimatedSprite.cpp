#include "AnimatedSprite.h"

#include <iostream>

#include "Texture2D.h"

namespace Render {
    AnimatedSprite::AnimatedSprite(const std::shared_ptr<Texture2D> p_Texture, const std::string &initialSubTexture2D,
        const std::shared_ptr<ShaderProgram> p_ShaderProgram, const glm::vec2 &position, const glm::vec2 &size,
        const float rotation) : Sprite(std::move(p_Texture),
                                       std::move(initialSubTexture2D),
                                       std::move(p_ShaderProgram),
                                       std::move(position),
                                       std::move(size),
                                       std::move(rotation))
    {
        m_pCurrentAnimationDuration = m_statesMap.end();
    }

    void AnimatedSprite::render() const {
        if (m_dirty) {
            const Texture2D::SubTexture2D& p_SubTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDuration->second[m_currentFrame].first);

            const GLfloat textureCoords[] = {
                // first triangle
                p_SubTexture.leftBottomUV.x, p_SubTexture.leftBottomUV.y,
                p_SubTexture.leftBottomUV.x, p_SubTexture.rightTopUV.y,
                p_SubTexture.rightTopUV.x,   p_SubTexture.rightTopUV.y,

                // second triangle
                p_SubTexture.rightTopUV.x,   p_SubTexture.rightTopUV.y,
                p_SubTexture.rightTopUV.x,   p_SubTexture.leftBottomUV.y,
                p_SubTexture.leftBottomUV.x, p_SubTexture.leftBottomUV.y,
            };

            glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            m_dirty = false;
        }
        Sprite::render();
    }

    void AnimatedSprite::setState(const std::string &newState) {
        StatesMap::const_iterator it = m_statesMap.find(std::move(newState));
        if (it == m_statesMap.end()) {
            std::cerr << "Can't find animation state " << newState << std::endl;
            return;
        }

        if (m_pCurrentAnimationDuration != it) {
            m_currentFrame = 0;
            m_currentAnimationTime = 0;

            m_pCurrentAnimationDuration = it;

            m_dirty = true;
        }

    }

    void AnimatedSprite::update(const uint64_t delta) {
        if (m_pCurrentAnimationDuration != m_statesMap.end()) {
            m_currentAnimationTime += delta;
            while (m_currentAnimationTime >= m_pCurrentAnimationDuration->second[m_currentFrame].second) {
                m_currentAnimationTime -= m_pCurrentAnimationDuration->second[m_currentFrame].second;
                ++m_currentFrame;
                m_dirty = true;
                if (m_currentFrame == m_pCurrentAnimationDuration->second.size()) {
                    m_currentFrame = 0;
                }
            }
        }
    }

    void AnimatedSprite::insertState(const std::string &state, std::vector<std::pair<std::string, size_t>> subTexturesDuration) {
        m_statesMap.emplace(std::move(state), std::move(subTexturesDuration));
    }
}
