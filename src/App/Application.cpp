#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Application.hpp"
#include "../Config.hpp"
#include "Log.hpp"

Application* Application::s_application = nullptr;

Application::Application() 
{
	glfwInit();
	p_window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "OpenGL template", NULL, NULL);
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(p_window);
	
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	glClearColor(0, 0, 0, 1);

#ifdef DEBUG
	const GLubyte* gpu = glGetString(GL_VERSION);
	const GLubyte* version = glGetString(GL_VERSION);
	std::string gpuName;
	std::string versionName;

	for (size_t i = 0; i < strlen((char*)gpu); i++)
	{
		gpuName += gpu[i];
	}

	for (size_t i = 0; i < strlen((char*)version); i++)
	{
		versionName += version[i];
	}

	Log::instance()->log("[INFO] OpenGL version : " + versionName + "\n", GREEN);
	Log::instance()->log("[INFO] GPU : " + gpuName, GREEN);
#endif

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(p_window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	p_sandbox = new Sandbox();
}

Application* Application::instance() noexcept
{
	if (s_application == nullptr)
	{
		s_application = new Application();
	}
	return s_application;
}

int Application::run()
{
	while (!glfwWindowShouldClose(p_window))
	{
		glfwPollEvents();

		float deltaTime = m_deltaTimer.getElapsedTime();	
		m_deltaTimer.restart();

		p_sandbox->update(deltaTime);

		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();	

		p_sandbox->render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(p_window);
	}

	return 0;
}

GLFWwindow* Application::getWindow() const noexcept
{
	return p_window;
}