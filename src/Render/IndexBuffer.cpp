#include "IndexBuffer.h"

namespace Render {
    IndexBuffer::IndexBuffer() : m_Id(0), m_count(0) {

    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_Id);
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept {
        m_Id = indexBuffer.m_Id;
        indexBuffer.m_Id = 0;
        m_count = indexBuffer.m_count;
        indexBuffer.m_count = 0;
        return *this;
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept {
        m_Id = indexBuffer.m_Id;
        m_count = indexBuffer.m_count;
        indexBuffer.m_Id = 0;
        indexBuffer.m_count = 0;
    }

    void IndexBuffer::init(const void *data, const unsigned int count) {

        m_count = count;
        glGenBuffers(1, &m_Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);

    }

    void IndexBuffer::bind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
    }

    void IndexBuffer::unbind() const{
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
