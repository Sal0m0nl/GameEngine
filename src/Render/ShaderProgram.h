#pragma once

#include <string>
#include "glad/glad.h"
#include "glm/mat4x4.hpp"

namespace Render
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertex_shader_source, const std::string& fragment_shader_source);
        ~ShaderProgram();
        bool isCompiled() const { return m_IsCompiled; }
        void use() const;
        void setInt(const std::string& name, const GLint value) const;
        void setMatrix4(const std::string& name, const glm::mat4 matrix);

        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram& ) = delete;
        ShaderProgram& operator=(const ShaderProgram& ) = delete;
        ShaderProgram& operator=(ShaderProgram&& shader_program) noexcept;
        ShaderProgram(ShaderProgram&& shader_program) noexcept;

    private:
        bool CreateShader(const std::string& shader_source, GLenum type, GLuint& id) const;
        bool m_IsCompiled = false;
        GLuint m_ShaderId = 0;
    };
}
