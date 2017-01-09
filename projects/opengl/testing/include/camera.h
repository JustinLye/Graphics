#pragma once

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace jlg {
	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVITY = 0.25f;
	const GLfloat ZOOM = 45.0f;
	enum Camera_Movement {
		FORWARD,
		BACK,
		LEFT,
		RIGHT
	};
	class Camera {
	protected:
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Right;
		glm::vec3 Up;
		glm::vec3 WorldUp;
		GLfloat Yaw;
		GLfloat Pitch;
		GLfloat Speed;
		GLfloat Sensitivity;
		GLfloat Zoom;
		void UpdateCameraVectors() {
			glm::vec3 front;
			front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
			front.y = sin(glm::radians(this->Pitch));
			front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
			this->Front = glm::normalize(front);
			this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
			this->Up = glm::normalize(glm::cross(this->Right, this->Front));
		}
	public:
		Camera(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			GLfloat yaw = YAW,
			GLfloat pitch = PITCH) :
			Front(glm::vec3(0.0f, 0.0f, -1.0f)),
			Speed(SPEED),
			Sensitivity(SENSITIVITY),
			Zoom(ZOOM) {
			this->Position = position;
			this->WorldUp = up;
			this->Yaw = yaw;
			this->Pitch = pitch;
			this->UpdateCameraVectors();
		}
		GLfloat GetZoom() const { return this->Zoom; }
		glm::mat4 GetViewMatrix() { return glm::lookAt(this->Position, this->Position + this->Front, this->Up); }
		void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime) {
			GLfloat velocity = this->Speed * deltaTime;
			if (direction == FORWARD) {
				this->Position += this->Front * velocity;
			}
			if (direction == BACK) {
				this->Position -= this->Front * velocity;
			}
			if (direction == LEFT) {
				this->Position -= this->Right * velocity;
			}
			if (direction == RIGHT) {
				this->Position += this->Right * velocity;
			}
		}
		void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
			xoffset *= this->Sensitivity;
			yoffset *= this->Sensitivity;
			this->Yaw += xoffset;
			this->Pitch += yoffset;
			if (constrainPitch) {
				if (this->Pitch > 89.0f)
					this->Pitch = 89.0f;
				if (this->Pitch < -89.0f)
					this->Pitch = -89.0f;
			}
			this->UpdateCameraVectors();
		}
		void ProcessMouseScroll(GLfloat yoffset) {
			if (this->Zoom >= 1.0f && this->Zoom <= 45.0f) {
				this->Zoom -= yoffset;
			}
			if (this->Zoom <= 1.0f)
				this->Zoom = 1.0f;
			if (this->Zoom >= 45.0f)
				this->Zoom = 45.0f;
		}
	};
};