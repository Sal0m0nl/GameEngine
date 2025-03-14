#pragma once

#include <memory>
#include <glm/vec2.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

namespace Render {

    class ShaderProgram;
    class Texture2D;

    class Sprite {
    public:
        Sprite(const std::shared_ptr<Texture2D> p_Texture, const std::string& initialSubTexture2D, const std::shared_ptr<ShaderProgram> p_ShaderProgram,
               const glm::vec2 &position = glm::vec2(0.f), const glm::vec2 &size = glm::vec2(1.f), const float rotation = 0.f);
        ~Sprite();

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        virtual void render() const;
        void setPosition(glm::vec2 position);
        void setSize(glm::vec2 size);
        void setRotation(float rotation);
    protected:
        std::shared_ptr<Texture2D> m_pTexture;
        std::shared_ptr<ShaderProgram> m_pShaderProgram;
        glm::vec2 m_Position;
        glm::vec2 m_Size;
        float m_Rotation;

        VertexBuffer m_vertexCoordsBuffer;
        VertexBuffer m_textureCoordsBuffer;
        IndexBuffer m_indexBuffer;

        VertexArray m_vertexArray;

    };
}
