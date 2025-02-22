#pragma once

#include <glad/glad.h>

namespace Render {

    class Texture2D {
    public:
        Texture2D(const GLuint width, const GLuint height, const unsigned char *pixels, const unsigned int channel = 4,
                  const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
        ~Texture2D();

        Texture2D();
        Texture2D(const Texture2D&) = delete;
        Texture2D(Texture2D&& texture_2d) noexcept;
        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&& texture_2d) noexcept;

        void bind() const;

    private:
        GLuint m_ID;
        GLenum m_mode;
        unsigned int m_width;
        unsigned int m_height;
    };
}


