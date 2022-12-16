#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Timer.hpp"
#include "Sandbox.hpp"

class Application 
{
private :
	Application();

public:
	static Application* instance() noexcept;

	int run();

	GLFWwindow* getWindow() const noexcept;

	Sandbox* getSandbox() noexcept; 

private :
	static Application* s_application;
	GLFWwindow* p_window;
	Timer m_deltaTimer;
	Sandbox* p_sandbox;
};