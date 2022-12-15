#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Render/Shader.hpp"

class Sandbox
{
public :
    Sandbox();

    void update(float deltaTime);

    void render();
    
private :
    Shader m_shader;
    int m_precision;
};