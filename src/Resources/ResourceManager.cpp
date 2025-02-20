#include "ResourceManager.h"
#include "../Render/ShaderProgram.h"
#include <sstream>
#include <fstream>
#include<iostream>


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



    std::shared_ptr<Render::ShaderProgram> ResourceManager::getShaderProgram(const std::string &shader_name) const {
        ShaderProgramsMap::const_iterator iterator = m_shaderPrograms_map.find(shader_name);
        if (iterator == m_shaderPrograms_map.end()) {
            std::cerr << "Can't find shader program with name " << shader_name << std::endl;
            return nullptr;
        }
        return iterator->second;
    }

    void ResourceManager::loadTexture(const std::string& name, const std::string& relative_path) {
        int channels = 0;
        int width = 0;
        int height = 0;

        stbi_set_flip_vertically_on_load(true);
        unsigned char* pixels = stbi_load(std::string(m_path + "\\" + relative_path).c_str(), &width, &height, &channels, 0);

        if (!pixels) {
            std::cerr << "FAILED TO LOAD TEXTURE WITH PATH " << relative_path << std::endl;
            return;
        }

        stbi_image_free(pixels);
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

