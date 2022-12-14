#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "Application.hpp"

Sandbox::Sandbox()
{
    std::uint32_t vboRect = 0;
    std::uint32_t vaoRect = 0;
    std::uint32_t eboRect = 0;
    glm::vec2 rectVertices[]
    {
        glm::vec2( 1,  1),
        glm::vec2( 1, -1),
        glm::vec2(-1, -1),
        glm::vec2(-1,  1)
    };

    std::uint32_t indices[]
    {
        0, 1, 3,
        1, 2, 3
    };

    m_shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glUseProgram(m_shader.getShaderID());

    glGenVertexArrays(1, &vaoRect);
    glBindVertexArray(vaoRect);

    glGenBuffers(1, &vboRect);
    glBindBuffer(GL_ARRAY_BUFFER, vboRect);
    glBufferData(GL_ARRAY_BUFFER, sizeof rectVertices, rectVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &eboRect);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboRect);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof glm::vec2, (void*)0);
}

void Sandbox::update(float deltaTime)
{
   
}

void Sandbox::render()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}