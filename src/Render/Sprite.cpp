#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include "Sprite.h"
#include "glad/glad.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "glm/ext/matrix_transform.hpp"


namespace Render {

    Sprite::Sprite(const std::shared_ptr<Texture2D> p_Texture, const std::shared_ptr<ShaderProgram> p_ShaderProgram,
        const glm::vec2 &position, const glm::vec2 &size, const float rotation) :
                                m_pTexture(std::move(p_Texture)),
                                m_pShaderProgram(std::move(p_ShaderProgram)),
                                m_Position(position),
                                m_Size(size),
                                m_Rotation(rotation)
    {
        const GLfloat vertexCoords[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
        };

        const GLfloat textureCoords[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,

            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
        };

        // VAO
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // texture coords VBO
        glGenBuffers(1, &m_vertexCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords),&textureCoords, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &m_textureCoordVBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords),&textureCoords, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    Sprite::~Sprite() {
        glDeleteBuffers(1, &m_vertexCoordsVBO);
        glDeleteBuffers(1, &m_textureCoordVBO);
        glDeleteVertexArrays(1, &m_VAO);
    }

    void Sprite::render() const {
        m_pShaderProgram->use();

        glm::mat4 modelMat(1.f);

        modelMat = glm::translate(modelMat, glm::vec3(m_Position, 0.0f));
        modelMat = glm::translate(modelMat, glm::vec3(0.5f * m_Size.x, 0.5f * m_Size.y, 0.0f));
        modelMat = glm::rotate(modelMat, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        modelMat = glm::translate(modelMat, glm::vec3(-0.5f * m_Size.x, -0.5f * m_Size.y, 0.0f));
        modelMat = glm::scale(modelMat, glm::vec3(m_Size, 1.0f));

        glBindVertexArray(m_VAO);
        m_pShaderProgram->setMatrix4("modelMatrix", modelMat);

        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void Sprite::setPosition(glm::vec2 position) {
        m_Position = position;
    }

    void Sprite::setSize(glm::vec2 size) {
        m_Size = size;
    }

    void Sprite::setRotation(float rotation) {
        m_Rotation = rotation;
    }
}

