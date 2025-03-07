#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>


namespace Render {
    class Texture2D;
    class ShaderProgram;
    class Sprite;
    class AnimatedSprite;
}

class ResourceManager {
public:
    static void setExecutablePath(const std::string& path);
    static void unloadAllResources();

    ~ResourceManager() = delete;
    ResourceManager() = delete;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;


    static std::shared_ptr<Render::ShaderProgram> loadShaderProgram(const std::string& shader_name, const std::string& vertex_shader_path, const std::string& fragment_shader_path);
    static std::shared_ptr<Render::Texture2D> loadTexture(const std::string& name, const std::string& relative_path);
    static std::shared_ptr<Render::Sprite> loadSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const std::string& subTextureName, const unsigned int width, const unsigned int height);
    static std::shared_ptr<Render::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const std::string& subTextureName, const unsigned int width, const unsigned int height);


    static std::shared_ptr<Render::Texture2D> getTexture(const std::string &texture_name);
    static std::shared_ptr<Render::Sprite> getSprite(const std::string &sprite_name);
    static std::shared_ptr<Render::AnimatedSprite> getAnimatedSprite(const std::string &sprite_name);
    static std::shared_ptr<Render::ShaderProgram> getShaderProgram(const std::string& shader_name);


    static std::shared_ptr<Render::Texture2D> loadTextuteAtlas(const std::string& texture_name, const std::string& relative_path, const std::vector<std::string> subTextures, const unsigned int subTextureWidth, const unsigned int subTextureHeight);

private:
    static std::string getStringFromFile(const std::string& relative_path_to_file);

    typedef std::map<const std::string, std::shared_ptr<Render::ShaderProgram>> ShaderProgramsMap;
    static ShaderProgramsMap m_shaderPrograms_map;

    typedef std::map<const std::string, std::shared_ptr<Render::Texture2D>> TexturesMap;
    static TexturesMap m_textures;

    typedef std::map<const std::string, std::shared_ptr<Render::Sprite>> SpritesMap;
    static SpritesMap m_SpritesMap;

    typedef std::map<const std::string, std::shared_ptr<Render::AnimatedSprite>> AnimatedSpritesMap;
    static AnimatedSpritesMap m_AnimatedSpritesMap;

    static std::string m_path;
};
