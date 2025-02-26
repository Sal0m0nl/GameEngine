#pragma once
#include <memory>
#include <string>
#include <glm/vec2.hpp>

class ShaderProgram;
class Texture2D;

namespace Render {
    class Sprite {
    public:
        Sprite(const std::shared_ptr<Texture2D> p_Texture, const std::shared_ptr<ShaderProgram> p_ShaderProgram,
               const glm::vec2 &position = glm::vec2(0.f), const glm::vec2 &size = glm::vec2(1.f), const float rotation = 0.f);
        ~Sprite() = default;

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        void render() const;
        void setPosition(glm::vec2 position);
        void setSize(glm::vec2 size);
        void setRotation(float rotation);
    private:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<Texture2D> m_pShaderProgram;
        glm::vec2 m_Position;
        glm::vec2 m_Size;
        float m_Rotation;
    };
}
