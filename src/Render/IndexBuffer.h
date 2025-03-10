#pragma once

#include "glad/glad.h"

namespace Render {
    class IndexBuffer {
    public:

        IndexBuffer();
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

        void init(const void* data, const unsigned int size);

        void bind();
        void unbind();

    private:
        GLuint m_Id;
    };
}

