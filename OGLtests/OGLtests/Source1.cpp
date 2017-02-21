

// Std. Includes
#include <string>
#include <vector>
#include <algorithm>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include <SOIL.h>

// Properties
GLuint screenWidth = 800, screenHeight = 600;

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();
GLuint loadTexture(GLchar* path, GLint textureWaping = GL_REPEAT);

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// The MAIN function, from here we start our application and run our Game loop
int main()
{
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	

							// Setup and compile our shaders
	Shader shader("shader.vs", "fragmentshader.frs");
	Shader BasicShader("BasicVertexShader.vs", "BasicFragmentShader.frs");
	

#pragma region "object_initialization"
	// Set the object data (buffers, vertex attributes)
	GLfloat cubeVertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
										  // Front face
										  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
										  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
										  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
										  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
										  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
										  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
																			// Left face
																			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
																			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
																			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
																			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
																			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
																			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
																											  // Right face
																											  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
																											  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
																											  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
																											  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
																											  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
																											  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
																																			   // Bottom face
																																			   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
																																			   0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
																																			   0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
																																			   0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
																																			   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
																																			   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
																																												 // Top face
																																												 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
																																												 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
																																												 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
																																												 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
																																												 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
																																												 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left          
};
	GLfloat planeVertices[] = {
		// Positions            // Texture Coords (note we set these higher than 1 that together with GL_REPEAT as texture wrapping mode will cause the floor texture to repeat)
		5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
		
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,


		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f,  -0.5f,  5.0f,  2.0f, 0.0f,
		5.0f,  -0.5f, -5.0f,  2.0f, 2.0f,
		
		
		
		
	};


	GLfloat transparentVertices[] = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	// Setup cube VAO
	GLuint cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
	// Setup plane VAO
	GLuint planeVAO, planeVBO;
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);


	GLuint transparentVAO, transparentVBO;
	glGenVertexArrays(1, &transparentVAO);
	glGenBuffers(1, &transparentVBO);
	glBindVertexArray(transparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
	

	// Load textures
	GLuint cubeTexture = loadTexture("container.jpg");
	GLuint floorTexture = loadTexture("container2.png");
	GLuint grassTexture = loadTexture("grass.png",GL_CLAMP_TO_EDGE);
	GLuint windowTexture = loadTexture("blending_transparent_window.png", GL_CLAMP_TO_EDGE);
	

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); // Set to always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);

#pragma endregion


	std::vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check and call events
		glfwPollEvents();
		Do_Movement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		// Draw objects
		shader.Use();
		glm::mat4 model;
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.Zoom, (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader.progId, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.progId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glStencilMask(0x00);
		// Floor
		glBindVertexArray(planeVAO);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		model = glm::mat4();
		glUniformMatrix4fv(glGetUniformLocation(shader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);




		

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		// Cubes
		glBindVertexArray(cubeVAO);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);  // We omit the glActiveTexture part since TEXTURE0 is already the default active texture unit. (sampler used in fragment is set to 0 as well as default)		
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0x00);
		glBindVertexArray(transparentVAO);
		glBindTexture(GL_TEXTURE_2D, windowTexture);
		glm::vec3 camPos(camera.Position);
		std::sort(vegetation.begin(), vegetation.end(), [](const glm::vec3& first, const glm::vec3& sec) {   
			return length(camera.Position - first) >= length(camera.Position - sec);
		});
		for (GLuint i = 0; i < vegetation.size(); ++i)
		{
			model = glm::mat4();
			model = glm::translate(model, vegetation[i]);
			glUniformMatrix4fv(glGetUniformLocation(shader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		glBindVertexArray(0);


		
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		BasicShader.Use();
		GLfloat scale = 1.05f;
		glUniformMatrix4fv(glGetUniformLocation(BasicShader.progId, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(BasicShader.progId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// Cubes
		glBindVertexArray(cubeVAO);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		glUniformMatrix4fv(glGetUniformLocation(BasicShader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		glUniformMatrix4fv(glGetUniformLocation(BasicShader.progId, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);


		
		
		// Swap the buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

// This function loads a texture from file. Note: texture loading functions like these are usually 
// managed by a 'Resource Manager' that manages all resources (like textures, models, audio). 
// For learning purposes we'll just define it as a utility function.
GLuint loadTexture(GLchar* path,GLint textureWaping)
{
	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWaping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWaping);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	return textureID;

}

#pragma region "User input"

// Moves/alters the camera positions based on user input
void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

#pragma endregion

