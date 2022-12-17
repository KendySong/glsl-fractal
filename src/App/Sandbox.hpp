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
    unsigned int m_locWinSize;
    unsigned int m_locPrecision;
    unsigned int m_locFractalType;
    unsigned int m_locAnimation;
    unsigned int m_locColorIn;
    unsigned int m_locColorOut;
    unsigned int m_locZoom;
    unsigned int m_locOffset;

    //FPS
    int m_fps;
    int m_tempFps;
    Timer m_fpsTimer; 

    //Input
    float m_sensitivity;
    glm::vec2 m_offset;
    glm::vec2 m_lastMouse;
    bool m_first;
    bool m_isClicking;

    //Choice of fractal
    FractalType m_fractalType;
    std::vector<const char*> fractalsTypeName;
    const char* m_currentName;

    //Fractal generation
    float m_zoom;
    int m_precision;
    glm::vec2 m_animation;
    glm::vec3 m_colorOut;
    glm::vec3 m_colorIn;
};