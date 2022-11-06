#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include "../Shader.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexArray.h"
#include "../BufferLayout.h"
#include "../Renderer.h"
#include "../Texture.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include <imgui/imgui_impl_opengl3.h>
#include "imgui/imgui_impl_glfw.h"
#include "Tests/TestClearColor.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 960;
const unsigned int SCR_HEIGHT = 560;



int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("Shaders/VertexShader.vs", "Shaders/FragmentShader.fs"); // you can name your shader files however you like

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		-50.0f, -50.f,  0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 50.0f, -50.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		 50.0f,  50.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-50.0f,  50.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	//unsigned int VBO, VAO, EBO;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	VertexBuffer vb(vertices,sizeof(vertices));
	IndexBuffer ib(indices,6);

	glm::mat4 proj = glm::ortho(0.0f,960.0f,0.0f,560.0f,-1.0f,1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	VertexArray va;

	BufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	va.AddBuffer(vb,layout);



	Renderer renderer;

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	ImGui_ImplOpenGL3_Init("#version 330");


	Texture t1("Resources/container.jpg");
	t1.Bind();

	glm::vec3 translationA(200, 200, 0);
	glm::vec3 translationB(400, 200, 0);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
		renderer.Clear();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		ImGui::Begin("Deneme");
		ImGui::SliderFloat3("TranslationA",&translationA.x,960.f,0.f);
		ImGui::SliderFloat3("TranslationB", &translationB.x, 960.f, 0.f);
		ImGui::Text("App average % .3f ms/frame (%.1f FPS)",1000.0f/ImGui::GetIO().Framerate,ImGui::GetIO().Framerate);
		ImGui::End();



		{

			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
			glm::mat4 mvp = proj * view * model;

			ourShader.Bind();
			ourShader.SetUniformMat4f("u_MVP", mvp);
			ourShader.SetUniform1i("ourTexture", 0);
			renderer.Draw(va, ib, ourShader);

		}

		{

			glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
			glm::mat4 mvp = proj * view * model;

			ourShader.Bind();
			ourShader.SetUniformMat4f("u_MVP", mvp);
			ourShader.SetUniform1i("ourTexture", 0);
			renderer.Draw(va, ib, ourShader);

		}
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);*/

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}