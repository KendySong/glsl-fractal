#pragma once
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Render/Shader.hpp"
#include "FractalType.hpp"
#include "Timer.hpp"

class Sandbox
{
public :
    Sandbox();

    void update(float deltaTime);

    void render();

    float& getZoom() noexcept;
    
private :
    Shader m_shader;

    int m_fps;
    int m_tempFps;
    Timer m_fpsTimer; 

    float m_sensitivity;
    glm::vec2 m_offset;
    glm::vec2 m_lastMouse;
    bool m_first;
    bool m_isClicking;

    float m_zoom;
    FractalType m_fractalType;
    std::vector<const char*> fractalsTypeName;
    const char* m_currentName;

    int m_precision;
    glm::vec2 m_animation;
    glm::vec3 m_colorOut;
    glm::vec3 m_colorIn;
};