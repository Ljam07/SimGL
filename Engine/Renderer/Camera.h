#include <glm/glm.hpp>

class Camera
{
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane,
		glm::vec3 pos, glm::vec3 rotation);

    void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

    void CalculateProjectionMatrix();
    void CalculateViewMatrix();
    void CalculateViewProjectionMatrix();
    void UpdateDirectionVectors();
    
    void SetPosition(const glm::vec3& position);
    void Translate(const glm::vec3& position);

    void SetRotation(const glm::vec3& rotation);
    void Rotate(const glm::vec3& rotation);

    const glm::vec3& GetPosition() const {return m_Position;}
    const glm::vec3& GetRotation() const {return m_Rotation;}

    const glm::mat4& GetProjectionMatrix() const {return m_ProjectionMatrix;}
    const glm::mat4& GetViewMatrix() const {return m_ViewMatrix;}
    const glm::mat4& GetViewProjectionMatrix() const {return m_ViewProjectionMatrix;}

    const glm::vec3 GetFront() const;
	const glm::vec3 GetRight() const;
	const glm::vec3 GetUp() const;
	const glm::vec3 GetWorldUp() const;

private:
    glm::vec3 m_LocalUp;
    glm::vec3 m_WorldUp = {0, 1.0f, 0};
    glm::vec3 m_Front = {0, 0, -1.0f};
    glm::vec3 m_Right = {1.0f, 0.0f, 0.0f};

    float m_FOV;
    float m_AspectRatio;
    float m_NearPlane;
    float m_FarPlane;

    glm::vec3 m_Rotation;
    glm::vec3 m_Position;

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;
};