#pragma once
#include <map>
#include <memory>
#include <string>

namespace Render {
    class ShaderProgram;
}

namespace ResourceManager
{
    class ResourceManager {
    public:
        ResourceManager(const std::string& path_to_executable);
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager) = delete;
        ResourceManager& operator=(ResourceManager&&) = delete;
        ResourceManager(ResourceManager&&) = delete;

        std::shared_ptr<Render::ShaderProgram> loadShaderProgram(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        std::shared_ptr<Render::ShaderProgram> getShaderProgram(const std::string& shader_name) const;

        void loadTexture(const std::string& name, const std::string& relative_path);

    private:
        std::string getStringFromFile(const std::string& relative_path_to_file) const;

        typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms_map;

        typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> TextureMap;
        TextureMap m_texturesMap;

        std::string m_path;
    };
}
