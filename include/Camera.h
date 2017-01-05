#pragma once

#include<vector>
#include<GL/glew.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


namespace jml {
	enum CameraMovement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVITY = 0.25f;
	const GLfloat ZOOM = 45.0f;
	const GLfloat PTICH_CONSTRAINT_MAX = 89.0f;
	const GLfloat PTICH_CONSTRAINT_MIN = -89.0f;
	const GLfloat ZOOM_MAX = 45.0f;
	const GLfloat ZOOM_MIN = 1.0f;
	const GLfloat FOV = 45.0f;
	const GLfloat CLIPPING_NEAR = 0.1f;
	const GLfloat CLIPPING_FAR = 1000.0f;

	class Camera {
	public:
		Camera(
			glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f),
			GLfloat Yaw = YAW,
			GLfloat Pitch = PITCH) :
			front(glm::vec3(0.0f, 0.0f, -1.0f)),
			speed(SPEED),
			sensitivity(SENSITIVITY),
			zoom(ZOOM) {
			this->position = Position;
			this->worldUp = up;
			this->yaw = Yaw;
			this->pitch = Pitch;
			this->UpdateCameraVectors();
		}

		glm::mat4 lookAt();
		virtual void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);
		virtual void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
		virtual void ProcessMouseScroll(GLfloat yOffset);
		GLfloat GetZoom() const { return this->zoom; }
	protected:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;

		GLfloat yaw;
		GLfloat pitch;
		GLfloat speed;
		GLfloat sensitivity;
		GLfloat zoom;
		
		virtual void UpdateCameraVectors();
	};
};


glm::mat4 jml::Camera::lookAt() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void jml::Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime) {
	GLfloat velocity = this->speed * deltaTime;
	switch (direction) {
	case FORWARD:
		this->position += this->front * velocity;
		break;
	case BACKWARD:
		this->position -= this->front * velocity;
		break;
	case LEFT:
		this->position -= this->right * velocity;
		break;
	case RIGHT:
		this->position += this->right * velocity;
		break;
	}
}
void jml::Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
	xOffset *= this->sensitivity;
	yOffset *= this->sensitivity;

	this->yaw += xOffset;
	this->pitch += yOffset;

	if (constrainPitch) {
		if (this->pitch > PTICH_CONSTRAINT_MAX)
			this->pitch = PTICH_CONSTRAINT_MAX;
		if (this->pitch < PTICH_CONSTRAINT_MIN)
			this->pitch = PTICH_CONSTRAINT_MIN;
	}
	this->UpdateCameraVectors();
}
void jml::Camera::ProcessMouseScroll(GLfloat yOffset) {
	if (this->zoom >= ZOOM_MIN && this->zoom <= ZOOM_MAX)
		this->zoom -= yOffset;
	if (this->zoom <= ZOOM_MIN)
		this->zoom = ZOOM_MIN;
	if (this->zoom >= ZOOM_MAX)
		this->zoom = ZOOM_MAX;

}

void jml::Camera::UpdateCameraVectors() {
	glm::vec3 Front;
	Front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	Front.y = sin(glm::radians(this->pitch));
	Front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(Front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}