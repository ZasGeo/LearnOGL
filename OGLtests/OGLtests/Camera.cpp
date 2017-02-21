#include "Camera.h"

void Camera::updateCameraVectors() {

	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	front.y = sin(glm::radians(this->Pitch));
	front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
	this->Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  
	this->Up = glm::normalize(glm::cross(this->Right, this->Front));
}

Camera::Camera(const glm::vec3& position, const glm::vec3& up, GLfloat yaw, GLfloat pitch )
	:Position{ position }, Front{ glm::vec3(0.0f,0.0f,-1.0f) }, Up{ glm::vec3(0.0f,1.0f,0.0f) }, Right{ glm::vec3(0.0f,1.0f,0.0f) }, WorldUp{ up }, Yaw{ yaw }, Pitch{ pitch }, MovementSpeed{ SPEED }, MouseSensitivity{ SENSITIVTY }, Zoom{ ZOOM }, MovingDirectionsCount{0}
{
	this->updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch)
	: Position{ glm::vec3(posX,posY,posZ) }, Front{ glm::vec3(0.0f,0.0f,-1.0f) }, Up{ glm::vec3(0.0f,1.0f,0.0f) }, Right{ glm::vec3(0.0f,1.0f,0.0f) }, WorldUp{ glm::vec3(upX,upY, upZ) }, Yaw{ yaw }, Pitch{ pitch }, MovementSpeed{ SPEED }, MouseSensitivity{ SENSITIVTY }, Zoom{ ZOOM }, MovingDirectionsCount{ 0 }
{
	this->updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
	
		GLfloat velocity = this->MovementSpeed * deltaTime;
		
		if (direction == FORWARD) {
			this->Position += this->Front * velocity;
			
		}
		if (direction == BACKWARD) {
			this->Position -= this->Front * velocity;
			
		}
		if (direction == LEFT) {
			this->Position -= this->Right * velocity;
			
		}
		if (direction == RIGHT) {
			this->Position += this->Right * velocity;
			
		}
	
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch) {

	xoffset *= this->MouseSensitivity;
	yoffset *= this->MouseSensitivity;

	this->Yaw = glm::mod(this->Yaw + xoffset, 360.0f);
	this->Pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->Pitch > 89.0f)
			this->Pitch = 89.0f;
		if (this->Pitch < -89.0f)
			this->Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();

}

void Camera::ProcessMouseScroll(GLfloat yoffset) {

	if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
		this->Zoom -= yoffset;

	if (this->Zoom <= 1.0f)
		this->Zoom = 1.0f;

	else if (this->Zoom >= 45.0f)
		this->Zoom = 45.0f;

}
