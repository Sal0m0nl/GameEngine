#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

namespace Render {

    class Renderer {
    public:
        static void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shaderProgram);

        static void setClearColor(float r, float g, float b, float alpha);

        static void clear();

        static void setViewport(unsigned int width, unsigned int height, unsigned int offsetX = 0, unsigned int offsetY= 0);

    };
}


