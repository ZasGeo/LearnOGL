//#define GLEW_STATIC
//#include <GL\glew.h>
//
//
//#include <glfw3.h>
//#include <iostream>
//#include <SOIL.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "Shader.h"
//#include "Camera.h"
//#include "Model.h"
//
//
//#define WINDOW_HEIGHT_Z 720.0f
//#define WINDOW_WIDTH_Z 1280.0f
//
//void key_callback(GLFWwindow*, int, int, int, int);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//glm::mat4 projection;
//
//bool firstMouse = true;
//bool keys[1024];
//GLfloat lastX = WINDOW_WIDTH_Z / 2.0f;
//GLfloat lastY = WINDOW_HEIGHT_Z / 2.0f;
//
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
//GLfloat currentFrame = 0.0f;
//
//
//// Light attributes
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//
//
//inline void MovmentUpdates();
//
//
//
//
//int main() {
//	
//	if (glfwInit()!=GLFW_TRUE) {
//		
//		std::cout << "Failed to init GLFW" << std::endl;
//		return -1;
//	}
//
//	
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	
//	
//
//	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH_Z, WINDOW_HEIGHT_Z, "OpenGlLearn", nullptr, nullptr);
//
//	if (window == nullptr) {
//		std::cout << "Failed to create window" << std::endl;
//		glfwTerminate();
//		return -1;
//
//	}
//
//
//	glfwMakeContextCurrent(window);
//
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	glewExperimental = GL_TRUE;
//
//	if (glewInit() != GLEW_OK) {
//		std::cout << "Failed to init GLEW" << std::endl;
//		glfwTerminate();
//		return -1;
//
//	}
//
//	GLint width, height;
//	glfwGetFramebufferSize(window, &width, &height);
//
//	glViewport(0, 0, width, height);
//
//
//	Shader LightningShader("lightningObjVertexShader.vs", "lightningObjFragmentShader.frs");
//
//	Shader LightningSourceShader("ligthningSourceVertexShader.vs", "lightningSourceFragmentShader.frs");
//
//	Model nanosuit("SuitModel/nanosuit/nanosuit.obj");
//
//	
//
//
//	glEnable(GL_DEPTH_TEST);
//
//	float mov = 0.0f;
//
//	while (!glfwWindowShouldClose(window)) {
//
//		
//
//		currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		//std::cout << (1 / deltaTime) << std::endl;
//
//		glfwPollEvents();
//		MovmentUpdates();
//
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
//
//
//		
//
//		LightningShader.Use();
//
//		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WINDOW_WIDTH_Z / (GLfloat)WINDOW_HEIGHT_Z, 0.1f, 1000.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glUniformMatrix4fv(glGetUniformLocation(LightningShader.progId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		glUniformMatrix4fv(glGetUniformLocation(LightningShader.progId, "view"), 1, GL_FALSE, glm::value_ptr(view));
//
//
//		// Draw the loaded model
//		glm::mat4 model;
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down
//		glUniformMatrix4fv(glGetUniformLocation(LightningShader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
//
//		nanosuit.Draw(LightningShader);
//
//		glfwSwapBuffers(window);
//	}
//
//	
//
//
//	glfwTerminate();
//	
//	return 0;
//}
//
//void key_callback(GLFWwindow *window, int key, int scanecode, int action, int mode)
//{
//
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	if (key >= 0 && key < 1024)
//	{
//		if (action == GLFW_PRESS)
//			keys[key] = true;
//		else if (action == GLFW_RELEASE)
//			keys[key] = false;
//	}
//}
//
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//
//inline void MovmentUpdates()
//{
//
//	// Camera controls
//	if (keys[GLFW_KEY_W])
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (keys[GLFW_KEY_S])
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (keys[GLFW_KEY_A])
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (keys[GLFW_KEY_D])
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//
//
//
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
