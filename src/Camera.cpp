//#include"..\include\Camera.h"
//
//
//
//glm::mat4 jml::Camera::lookAt() {
//	return glm::lookAt(this->position, this->position + this->front, this->up);
//}
//
//void jml::Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime) {
//	GLfloat velocity = this->speed * deltaTime;
//	switch (direction) {
//	case FORWARD:
//		this->position += this->front * velocity;
//		break;
//	case BACKWARD:
//		this->position -= this->front * velocity;
//		break;
//	case LEFT:
//		this->position -= this->right * velocity;
//		break;
//	case RIGHT:
//		this->position += this->right * velocity;
//		break;
//	}
//}
//void jml::Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch) {
//	xOffset *= this->sensitivity;
//	yOffset *= this->sensitivity;
//
//	this->yaw += xOffset;
//	this->pitch += yOffset;
//	
//	if (constrainPitch) {
//		if(this->pitch > PTICH_CONSTRAINT_MAX)
//			this->pitch = PTICH_CONSTRAINT_MAX;
//		if(this->pitch < PTICH_CONSTRAINT_MIN)
//			this->pitch = PTICH_CONSTRAINT_MIN;
//	}
//	this->UpdateCameraVectors();
//}
//void jml::Camera::ProcessMouseScroll(GLfloat yOffset) {
//	if(this->zoom >= ZOOM_MIN && this->zoom <= ZOOM_MAX)
//		this->zoom -= yOffset;
//	if(this->zoom <= ZOOM_MIN)
//		this->zoom = ZOOM_MIN;
//	if(this->zoom >= ZOOM_MAX)
//		this->zoom = ZOOM_MAX;
//
//}
//
//void jml::Camera::UpdateCameraVectors() {
//	glm::vec3 Front;
//	Front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
//	Front.y = sin(glm::radians(this->pitch));
//	Front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
//	this->front = glm::normalize(front);
//	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
//	this->up = glm::normalize(glm::cross(this->right, this->front));
//}