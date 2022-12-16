#include <iostream>
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "Sandbox.hpp"
#include "../Config.hpp"
#include "Application.hpp"

Sandbox::Sandbox()
{
    m_fps = 0;
    m_tempFps = 0;
    m_zoom = 4;
    m_first = true;
    m_sensitivity = 0.001;

    m_precision = 50;
    m_animation = glm::vec2(0);
    fractalsTypeName = { "Mandelbrot", "Julia", "Burning Ship"};
    m_fractalType = FractalType::mandelbrot;
    m_currentName = fractalsTypeName[0];

    m_colorOut = glm::vec3(0, 1, 0);
    m_colorIn = glm::vec3(0);

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
    GLFWwindow* window = Application::instance()->getWindow();

    m_fps++;
    if (m_fpsTimer.getElapsedTime() >= 1)
    {
        m_tempFps = m_fps;
        m_fps = 0;
        m_fpsTimer.restart();       
    }

    int winSizeX;
    int winSizeY;
    glfwGetWindowSize(window, &winSizeX, &winSizeY);
    unsigned locWinSize = glGetUniformLocation(m_shader.getShaderID(), "u_windowSize");
    glUniform2fv(locWinSize, 1, glm::value_ptr(glm::vec2(winSizeX, winSizeY)));

    unsigned int locPrecision = glGetUniformLocation(m_shader.getShaderID(), "u_precision");
    glUniform1i(locPrecision, m_precision);

    unsigned int locFractalType = glGetUniformLocation(m_shader.getShaderID(), "u_fractalType");
    glUniform1i(locFractalType, (int)m_fractalType);

    unsigned int locAnimation = glGetUniformLocation(m_shader.getShaderID(), "u_animation");
    glUniform2fv(locAnimation, 1, glm::value_ptr(m_animation));

    unsigned int locColorIn = glGetUniformLocation(m_shader.getShaderID(), "u_colorIn");
    glUniform3fv(locColorIn, 1, glm::value_ptr(m_colorIn));

    unsigned int locColorOut = glGetUniformLocation(m_shader.getShaderID(), "u_colorOut");
    glUniform3fv(locColorOut, 1, glm::value_ptr(m_colorOut));

    unsigned int locZoom = glGetUniformLocation(m_shader.getShaderID(), "u_zoom");
    glUniform1f(locZoom, m_zoom);

    unsigned int locOffset = glGetUniformLocation(m_shader.getShaderID(), "u_offset");
    glUniform2fv(locOffset, 1, glm::value_ptr(m_offset));
   
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        glm::vec2 currentMouse = glm::vec2(x, y);

        if (m_first)
        {
            m_lastMouse = currentMouse;
            m_first = false;
        }

        if (!m_isClicking)
        {
            m_lastMouse = currentMouse;
            m_isClicking = true;
        }

        glm::vec2 offset = currentMouse - m_lastMouse;
        offset *= m_sensitivity;

        m_offset.x -= offset.x;
        m_offset.y += offset.y;
        m_lastMouse = currentMouse;
        m_isClicking = true;
    }
    else if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        m_isClicking = false;
    }
}

void Sandbox::render()
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    ImGui::Begin("Render");
    ImGui::Text("FPS : %d", m_tempFps);
    ImGui::ColorEdit3("Out color", &m_colorOut.x);
    ImGui::ColorEdit3("In color", &m_colorIn.x);

    ImGui::SliderInt("Precision", &m_precision, 1, 1000);
    if (ImGui::BeginCombo("Fractal", m_currentName))
    {
        for (size_t i = 0; i < fractalsTypeName.size(); i++)
        {
            if (ImGui::Selectable(fractalsTypeName[i]))
            {
                m_fractalType = static_cast<FractalType>(i);
                m_currentName = fractalsTypeName[i];
                ImGui::SetItemDefaultFocus();
            }       
        }
        ImGui::EndCombo();
    }

    ImGui::InputFloat("Zoom", &m_zoom);

    ImGui::SliderFloat("Offset X", &m_offset.x, -10, 10);
    ImGui::SliderFloat("Offset Y", &m_offset.y, -10, 10);

    if (m_currentName == "Julia")
    {
        ImGui::TextUnformatted("Animation");
        ImGui::Separator();
        ImGui::SliderFloat(" X", &m_animation.x, -2.7, 1.7);
        ImGui::SliderFloat(" Y", &m_animation.y, -2.7, 1.7);
    }
    ImGui::End();
}

float& Sandbox::getZoom() noexcept
{
    return m_zoom;
}