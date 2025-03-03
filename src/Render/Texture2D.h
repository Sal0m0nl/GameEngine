#pragma once

#include <map>
#include <string>
#include <glad/glad.h>

#include "glm/vec2.hpp"

namespace Render {

    class Texture2D {
    public:

        struct SubTexture2D {
            glm::vec2 leftBottomUV;
            glm::vec2 rightTopUV;

            SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV)
                : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV){}

            SubTexture2D()
                : leftBottomUV(0.f), rightTopUV(1.f) {}
        };

        Texture2D(const GLuint width, const GLuint height, const unsigned char *pixels, const unsigned int channel = 4,
                  const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
        ~Texture2D();

        Texture2D();
        Texture2D(const Texture2D&) = delete;
        Texture2D(Texture2D&& texture_2d) noexcept;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&& texture_2d) noexcept;

        void addSubTexture(const std::string& name, const glm::vec2 leftBottomUV, const glm::vec2 rightTopUV);

        const SubTexture2D& getSubTexture(const std::string& name) const;
        const unsigned int& getWidth() const;
        const unsigned int& getHeight() const;

        void bind() const;

    private:
        GLuint m_ID;
        GLenum m_mode;
        unsigned int m_width;
        unsigned int m_height;

        std::map<std::string, SubTexture2D> m_subTextures;
    };
}


