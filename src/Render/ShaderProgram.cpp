#include "ShaderProgram.h"

#include <iostream>

namespace Render
{

    bool ShaderProgram::CreateShader(const std::string& shader_source, GLenum type, GLuint &id) const
    {
        // creating shader
        id = glCreateShader(type);
        const char* source = shader_source.c_str();
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id);

        // checking status
        GLint status;
        glGetShaderiv(id, GL_COMPILE_STATUS, &status);
        if (!status)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::cerr << "ERROR WHILE COMPILING SHADER:\n " << infoLog << std::endl;
            return false;
        }
        return true;
    }

    ShaderProgram::ShaderProgram(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
    {
        // create vertex shader
        GLuint vertex_shader;
        if (!CreateShader(vertex_shader_source, GL_VERTEX_SHADER, vertex_shader))
        {
            std::cerr << "ERROR WHILE COMPILING VERTEX SHADER" << std::endl;
            return;
        }

        // create fragment shader
        GLuint fragment_shader;
        if (!CreateShader(fragment_shader_source, GL_FRAGMENT_SHADER, fragment_shader))
        {
            std::cerr << "ERROR WHILE COMPILING FRAGMENT SHADER" << std::endl;
            glDeleteShader(vertex_shader);
            return;
        }

        // create shader program
        m_ShaderId = glCreateProgram();
        glAttachShader(m_ShaderId, vertex_shader);
        glAttachShader(m_ShaderId, fragment_shader);
        glLinkProgram(m_ShaderId);

        // deleting vertex&fragment shaders
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        // checking status
        GLint status;
        glGetProgramiv(m_ShaderId, GL_LINK_STATUS, &status);
        if (!status)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(m_ShaderId, 1024, nullptr, infoLog);
            std::cerr << "ERROR WHILE LINKING SHADER PROGRAM:\n " << infoLog << std::endl;
            m_IsCompiled = false;
            return;
        }
        m_IsCompiled = true;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ShaderId);
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_ShaderId);
    }

    void ShaderProgram::setInt(const std::string &name, const GLint value) const
    {
        glUniform1i(glGetUniformLocation(m_ShaderId, name.c_str()), value);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shader_program) noexcept
    {
        glDeleteProgram(m_ShaderId);
        m_ShaderId = shader_program.m_ShaderId;
        m_IsCompiled = shader_program.isCompiled();
        shader_program.m_ShaderId = 0;
        shader_program.m_IsCompiled = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shader_program) noexcept
    {
        m_ShaderId = shader_program.m_ShaderId;
        m_IsCompiled = shader_program.isCompiled();
        shader_program.m_ShaderId = 0;
    }

}
