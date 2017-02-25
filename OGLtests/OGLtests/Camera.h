#ifndef _CAMERA9645_
#define _CAMERA9645_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

#define YAW  -90.0f
#define PITCH  0.0f
#define SPEED  3.0f
#define SENSITIVTY 0.10f
#define ZOOM 45.0f

class Camera {
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;
	

	// Constructor with vectors
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);
	
	
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

	inline glm::mat4 GetViewMatrix() const {
		return glm::lookAt(Position,Position + Front, this->Up);
	}
	

	inline glm::mat4 GetReverseViewMatrix() const {
		return glm::lookAt(Position, Position +(- Front), this->Up);
	}

	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
	
	
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
	

	// Processes input received from a mouse scroll-wheel event
	void ProcessMouseScroll(GLfloat yoffset);
	

private:

	GLint MovingDirectionsCount;

	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors();

		
};

#endif // !_CAMERA9645_

