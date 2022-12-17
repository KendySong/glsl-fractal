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

    m_locWinSize = glGetUniformLocation(m_shader.getShaderID(), "u_windowSize");
    m_locPrecision = glGetUniformLocation(m_shader.getShaderID(), "u_precision");
    m_locFractalType = glGetUniformLocation(m_shader.getShaderID(), "u_fractalType");
    m_locAnimation = glGetUniformLocation(m_shader.getShaderID(), "u_animation");
    m_locColorIn = glGetUniformLocation(m_shader.getShaderID(), "u_colorIn");
    m_locColorOut = glGetUniformLocation(m_shader.getShaderID(), "u_colorOut");
    m_locZoom = glGetUniformLocation(m_shader.getShaderID(), "u_zoom");
    m_locOffset = glGetUniformLocation(m_shader.getShaderID(), "u_offset");
}

void Sandbox::update(float deltaTime)
{
    int winSizeX, winSizeY;
    GLFWwindow* window = Application::instance()->getWindow();

    m_fps++;
    if (m_fpsTimer.getElapsedTime() >= 1)
    {
        m_tempFps = m_fps;
        m_fps = 0;
        m_fpsTimer.restart();       
    }

    //Camera movement
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
        offset *= m_sensitivity * m_zoom;

        m_offset.x -= offset.x;
        m_offset.y += offset.y;
        m_lastMouse = currentMouse;
        m_isClicking = true;
    }
    else if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        m_isClicking = false;
    }
    
    glfwGetWindowSize(window, &winSizeX, &winSizeY);
    glUniform2fv(m_locWinSize, 1, glm::value_ptr(glm::vec2(winSizeX, winSizeY)));
    glUniform1i(m_locPrecision, m_precision);
    glUniform1i(m_locFractalType, (int)m_fractalType);
    glUniform2fv(m_locAnimation, 1, glm::value_ptr(m_animation));
    glUniform3fv(m_locColorIn, 1, glm::value_ptr(m_colorIn));
    glUniform3fv(m_locColorOut, 1, glm::value_ptr(m_colorOut));
    glUniform1f(m_locZoom, m_zoom);
    glUniform2fv(m_locOffset, 1, glm::value_ptr(m_offset));   
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