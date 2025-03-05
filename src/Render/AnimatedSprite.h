#pragma once

#include <map>
#include <vector>

#include "Sprite.h"

namespace Render {
    class AnimatedSprite : public Sprite {
    public:
        AnimatedSprite(const std::shared_ptr<Texture2D> p_Texture, const std::string& initialSubTexture2D, const std::shared_ptr<ShaderProgram> p_ShaderProgram,
               const glm::vec2 &position = glm::vec2(0.f), const glm::vec2 &size = glm::vec2(1.f), const float rotation = 0.f);

        void render() const override;

        void setState(const std::string& newState);
        void update(const uint64_t delta);

        void insertState(const std::string& state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration);

    private:
        typedef std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> StatesMap;
        StatesMap m_statesMap;

        size_t m_currentFrame = 0;
        uint64_t m_currentAnimationTime = 0;

        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDuration;

        mutable bool m_dirty = false;

    };
}

