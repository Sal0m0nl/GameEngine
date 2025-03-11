#include "VertexBuffer.h"

namespace Render {
    VertexBuffer::VertexBuffer() : m_Id(0) {

    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &m_Id);
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer &&vertexBuffer) noexcept {
        m_Id = vertexBuffer.m_Id;
        vertexBuffer.m_Id = 0;
        return *this;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept {
        m_Id = vertexBuffer.m_Id;
        vertexBuffer.m_Id = 0;
    }

    void VertexBuffer::init(const void *data, const unsigned int size) {

        glGenBuffers(1, &m_Id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    }

    void VertexBuffer::update(const void *data, const unsigned int size) const {

        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
