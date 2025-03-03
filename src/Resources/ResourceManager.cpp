#include <sstream>
#include <fstream>
#include<iostream>

#include "../Render/Texture2D.h"
#include "ResourceManager.h"
#include "../Render/ShaderProgram.h"
#include "../Render/Sprite.h"

#define STB_IMAGE_IMPLEMENTATION

#include "../../res/Textures/stb_image.h"



namespace ResourceManager {



    ResourceManager::ResourceManager(const std::string& path_to_executable) {
        std::size_t found = path_to_executable.find_last_of("/\\");
        m_path = path_to_executable.substr(0, found);
    }



    std::shared_ptr<Render::ShaderProgram> ResourceManager::loadShaderProgram(const std::string &shader_name, const std::string &vertex_shader_path, const std::string &fragment_shader_path) {

        // reading vertex shader
        std::string vertex_shader_source = getStringFromFile(vertex_shader_path);
        if (vertex_shader_source.empty()) {
            std::cerr << "ERROR WHILE READING FILE " << vertex_shader_path << std::endl;
            return nullptr;
        }

        // reading fragment shader
        std::string fragment_shader_source = getStringFromFile(fragment_shader_path);
        if (fragment_shader_path.empty()) {
            std::cerr << "ERROR WHILE READING FILE " << fragment_shader_path << std::endl;
            return nullptr;
        }

        // emplacing shader program to the map
        std::shared_ptr<Render::ShaderProgram>& shader_program = m_shaderPrograms_map.emplace(shader_name, std::make_shared<Render::ShaderProgram>(vertex_shader_source, fragment_shader_source)).first->second;

        if (shader_program->isCompiled())
            return shader_program;

        std::cerr << "ERROR WHILE COMPILING SHADER PROGRAM " << shader_name << " with vertex shader: " << vertex_shader_path << " and fragment shader: " << fragment_shader_path << std::endl;
        return nullptr;
    }

    std::shared_ptr<Render::Texture2D> ResourceManager::loadTexture(const std::string &name,
                                                                    const std::string &relative_path) {
        int channels = 0;
        int width = 0;
        int height = 0;

        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixels = stbi_load(std::string(m_path + "\\" + relative_path).c_str(), &width, &height, &channels, 0);

        if (!pixels) {
            std::cerr << "FAILED TO LOAD TEXTURE WITH PATH " << relative_path << std::endl;
            return nullptr;
        }

        std::shared_ptr<Render::Texture2D> newTexture = m_textures.emplace(name, std::make_shared<Render::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

        stbi_image_free(pixels);

        return newTexture;
    }

    std::shared_ptr<Render::Sprite> ResourceManager::loadSprite(const std::string &spriteName,
        const std::string &textureName, const std::string &shaderName, const std::string& subTextureName, const unsigned int width,
        const unsigned int height) {

        std::shared_ptr<Render::Texture2D> p_Texture = getTexture(textureName);
        if (!p_Texture) {
            std::cerr << "Error while loading sprite with name: " << spriteName << std::endl;
            return nullptr;
        }
        std::shared_ptr<Render::ShaderProgram> p_ShaderProgram = getShaderProgram(shaderName);
        if (!p_ShaderProgram) {
            std::cerr << "Error while loading sprite with name: " << shaderName << std::endl;
            return nullptr;
        }

        std::shared_ptr<Render::Sprite> newSprite = m_SpritesMap.emplace(spriteName, std::make_shared<Render::Sprite>(p_Texture, subTextureName, p_ShaderProgram, glm::vec2(0.0f, 0.0f), glm::vec2(width, height), 0.f)).first->second;

        return newSprite;

    }

    std::shared_ptr<Render::ShaderProgram> ResourceManager::getShaderProgram(const std::string &shader_name) const {
        ShaderProgramsMap::const_iterator iterator = m_shaderPrograms_map.find(shader_name);
        if (iterator == m_shaderPrograms_map.end()) {
            std::cerr << "Can't find shader program with name " << shader_name << std::endl;
            return nullptr;
        }
        return iterator->second;
    }

    std::shared_ptr<Render::Texture2D> ResourceManager::getTexture(const std::string &texture_name) const {
        TexturesMap::const_iterator it = m_textures.find(texture_name);
        if (it != m_textures.end()) {
            return it->second;
        }
        std::cerr << "Can't get texture with name " << texture_name << std::endl;
        return nullptr;
    }

    std::shared_ptr<Render::Sprite> ResourceManager::getSprite(const std::string &sprite_name) const {
        SpritesMap::const_iterator it = m_SpritesMap.find(sprite_name);
        if (it != m_SpritesMap.end()) {
            return it->second;
        }
        std::cerr << "Can't get sprite with name " << sprite_name << std::endl;
        return nullptr;
    }

    std::shared_ptr<Render::Texture2D> ResourceManager::loadTextuteAtlas(const std::string &texture_name,
        const std::string &relative_path, const std::vector<std::string> subTextures, const unsigned int subTextureWidth,
        const unsigned int subTextureHeight) {

        std::shared_ptr<Render::Texture2D> p_Texture = loadTexture(std::move(texture_name), std::move(relative_path));

        if (p_Texture) {
            const unsigned int textureWidth = p_Texture->getWidth();
            const unsigned int textureHeight = p_Texture->getHeight();

            unsigned int currentTextureOffsetX = 0;
            unsigned int currentTextureOffsetY = textureHeight;

            for (const std::string& currentSubTexture : subTextures) {
                glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);
                glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);

                currentTextureOffsetX += subTextureWidth;
                if (currentTextureOffsetX >= textureWidth) {
                    currentTextureOffsetX = 0;
                    currentTextureOffsetY -= subTextureHeight;
                }

                p_Texture->addSubTexture(std::move(currentSubTexture), leftBottomUV, rightTopUV);
            }

        }
        return p_Texture;
    }


    std::string ResourceManager::getStringFromFile(const std::string& relative_path_to_file) const {

        std::ifstream f(m_path + "\\" + relative_path_to_file.c_str(), std::ios::in | std::ios::binary);

        if (!f.is_open()) {
            std::cerr << "Can't open file with path: " << m_path << "/" << relative_path_to_file.c_str() << std::endl;
            return std::string{};
        }

        std::stringstream buffer;
        buffer << f.rdbuf();
        f.close();
        return buffer.str();
    }


}

