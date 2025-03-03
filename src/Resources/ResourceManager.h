#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>


namespace Render {
    class Texture2D;
    class ShaderProgram;
    class Sprite;
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

        std::shared_ptr<Render::Texture2D> loadTexture(const std::string& name, const std::string& relative_path);
        std::shared_ptr<Render::Sprite> loadSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const std::string& subTextureName, const unsigned int width, const unsigned int height);


        std::shared_ptr<Render::Texture2D> getTexture(const std::string &texture_name) const;
        std::shared_ptr<Render::Sprite> getSprite(const std::string &sprite_name) const;

        std::shared_ptr<Render::Texture2D> loadTextuteAtlas(const std::string& texture_name, const std::string& relative_path, const std::vector<std::string> subTextures, const unsigned int subTextureWidth, const unsigned int subTextureHeight);

    private:
        std::string getStringFromFile(const std::string& relative_path_to_file) const;

        typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramsMap;
        ShaderProgramsMap m_shaderPrograms_map;

        typedef std::map<const std::string, std::shared_ptr<Render::Texture2D>> TexturesMap;
        TexturesMap m_textures;

        typedef std::map<const std::string, std::shared_ptr<Render::Sprite>> SpritesMap;
        SpritesMap m_SpritesMap;

        std::string m_path;
    };
}
