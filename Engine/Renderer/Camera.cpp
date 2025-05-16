#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane,
		glm::vec3 pos, glm::vec3 rotation)
        : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearPlane(nearPlane), m_FarPlane(farPlane),
		m_Position(pos), m_Rotation(rotation) 
{

}

void Camera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    m_FOV = fov;
	m_AspectRatio = aspectRatio;
	m_NearPlane = nearPlane;
	m_FarPlane = farPlane;
	CalculateProjectionMatrix();
}

void Camera::CalculateViewMatrix()
{

}

void Camera::CalculateProjectionMatrix()
{
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearPlane, m_FarPlane);
}

void Camera::CalculateViewProjectionMatrix()
{

}

void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
	CalculateViewMatrix();
}

void Camera::Translate(const glm::vec3& position)
{

}

void Camera::SetRotation(const glm::vec3& rotation)
{
    m_Rotation = rotation;
	UpdateDirectionVectors();
	CalculateViewMatrix();
}

void Camera::Rotate(const glm::vec3& rotation)
{

}


void Camera::UpdateDirectionVectors()
{
    float yaw = glm::radians(m_Rotation.y);
	float pitch = glm::radians(m_Rotation.x);

	glm::vec3 front;
	front.x = cos(yaw) * cos(pitch);
	front.y = sin(pitch);
	front.z = sin(yaw) * cos(pitch);
	m_Front = glm::normalize(front);

	// Recalculate Right and Up vectors
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_LocalUp = glm::normalize(glm::cross(m_Right, m_Front));
}