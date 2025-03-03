#include "Texture2D.h"

#include <iostream>
#include <memory>
#include <glad/glad.h>


namespace Render {
    Texture2D::Texture2D(const GLuint width, const GLuint height, const unsigned char *pixels,
        const unsigned int channel, const GLenum filter, const GLenum wrapMode): m_width(width), m_height(height) {

        switch (channel) {
            case 4:
                m_mode = GL_RGBA;
                break;
            case 3:
                m_mode = GL_RGB;
                break;
            default:
                m_mode = GL_RGB;
                break;
        }

        // generate texture
        glGenTextures(1, &m_ID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        // settings of texture
        glTexImage2D(GL_TEXTURE_2D, 0, m_mode, width, height, 0, m_mode, GL_UNSIGNED_BYTE, pixels);


        // texture parameters
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        // mip map
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_ID);
    }

    Texture2D::Texture2D(Texture2D &&texture_2d) noexcept {
        m_ID = texture_2d.m_ID;
        texture_2d.m_ID = 0;
        m_mode = texture_2d.m_mode;
        m_width = texture_2d.m_width;
        m_height = texture_2d.m_height;
    }

    Texture2D& Texture2D::operator=(Texture2D&& texture_2d) noexcept {
        glDeleteTextures(1, &m_ID);
        m_ID = texture_2d.m_ID;
        texture_2d.m_ID = 0;
        m_mode = texture_2d.m_mode;
        m_width = texture_2d.m_width;
        m_height = texture_2d.m_height;
        return *this;
    }

    void Texture2D::addSubTexture(const std::string &name, const glm::vec2 leftBottomUV, const glm::vec2 rightTopUV) {
        m_subTextures.emplace(std::move(name), SubTexture2D(leftBottomUV, rightTopUV));
    }

    const Texture2D::SubTexture2D& Texture2D::getSubTexture(const std::string &name) const {
        auto it = m_subTextures.find(name);
        if (it != m_subTextures.end()) {
            return it->second;
        }
        const static SubTexture2D defaultSubTexture;
        return defaultSubTexture;
    }

    const unsigned int& Texture2D::getWidth() const {
        return m_width;
    }

    const unsigned int& Texture2D::getHeight() const {
        return m_height;
    }

    void Texture2D::bind() const {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }
}
