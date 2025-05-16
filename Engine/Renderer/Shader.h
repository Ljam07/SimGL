#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class Shader
{
public:
    // Constructors for graphics shaders
    Shader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    // Constructor for compute shader
    Shader(const std::string& name, const std::string& computeSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Uniform setters
    void SetMat4(const std::string& name, const glm::mat4& value);
    void SetInt(const std::string& name, int value);
    void SetIntArray(const std::string& name, int* values, uint32_t count);
    void SetFloat(const std::string& name, float value);
    void SetFloat3(const std::string& name, const glm::vec3& value);
    void SetFloat4(const std::string& name, const glm::vec4& value);

    const std::string& GetName() const { return m_Name; }

    // Factory methods
    static std::shared_ptr<Shader> Create(const std::string& filepath);
    static std::shared_ptr<Shader> Create(const std::string& name,
                                          const std::string& vertexSrc,
                                          const std::string& fragmentSrc);
    static std::shared_ptr<Shader> CreateCompute(const std::string& name,
                                                 const std::string& computeSrc);

private:
    std::string m_Name;
    uint32_t m_RendererID = 0;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;

    int GetUniformLocation(const std::string& name) const;
    void UploadUniformInt(const std::string& name, int value);
    void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
    void UploadUniformFloat(const std::string& name, float value);
    void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
    void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
    void UploadUniformMat4(const std::string& name, const glm::mat4& value);
};

class ShaderLibrary
{
public:
    void Add(const std::shared_ptr<Shader>& shader);
    void Add(const std::string& name, const std::shared_ptr<Shader>& shader);

    std::shared_ptr<Shader> Load(const std::string& filepath);
    std::shared_ptr<Shader> Load(const std::string& name, const std::string& filepath);

    std::shared_ptr<Shader> Get(const std::string& name);
    bool Exists(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};