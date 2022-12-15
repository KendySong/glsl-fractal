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
    
private :
    int m_fps;
    int m_tempFps;
    Timer m_fpsTimer;

    Shader m_shader;
    int m_precision;

    FractalType m_fractalType;
    std::vector<const char*> fractalsTypeName;
    const char* m_currentName;

    glm::vec2 m_animation;
    glm::vec3 m_colorOut;
    glm::vec3 m_colorIn;
};