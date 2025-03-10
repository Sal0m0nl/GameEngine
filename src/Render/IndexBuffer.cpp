#include "IndexBuffer.h"

namespace Render {
    IndexBuffer::IndexBuffer() : m_Id(0) {

    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_Id);
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept {
        m_Id = indexBuffer.m_Id;
        indexBuffer.m_Id = 0;
        return *this;
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept {
        m_Id = indexBuffer.m_Id;
        indexBuffer.m_Id = 0;
    }

    void IndexBuffer::init(const void *data, const unsigned int size) {

        glGenBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    }

    void IndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void IndexBuffer::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
