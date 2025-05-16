// Shader.cpp
#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

static std::string ReadFile(const std::string& filepath)
{
    std::ifstream stream(filepath, std::ios::in | std::ios::binary);
    if (!stream)
    {
        std::cerr << "Could not open file: " << filepath << std::endl;
        return "";
    }
    std::ostringstream ss;
    ss << stream.rdbuf();
    return ss.str();
}

Shader::Shader(const std::string& name,
               const std::string& vertexSrc,
               const std::string& fragmentSrc)
    : m_Name(name)
{
    // Compile vertex shader
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* src = vertexSrc.c_str();
    glShaderSource(vertexShader, 1, &src, nullptr);
    glCompileShader(vertexShader);
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader compilation failed: " << infoLog << std::endl;
    }

    // Compile fragment shader
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    src = fragmentSrc.c_str();
    glShaderSource(fragmentShader, 1, &src, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader compilation failed: " << infoLog << std::endl;
    }

    // Link program
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vertexShader);
    glAttachShader(m_RendererID, fragmentShader);
    glLinkProgram(m_RendererID);
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const std::string& name,
               const std::string& computeSrc)
    : m_Name(name)
{
    // Compile compute shader
    uint32_t computeShader = glCreateShader(GL_COMPUTE_SHADER);
    const char* src = computeSrc.c_str();
    glShaderSource(computeShader, 1, &src, nullptr);
    glCompileShader(computeShader);
    int success;
    glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(computeShader, 512, nullptr, infoLog);
        std::cerr << "Compute shader compilation failed: " << infoLog << std::endl;
    }

    // Link program
    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, computeShader);
    glLinkProgram(m_RendererID);
    glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_RendererID, 512, nullptr, infoLog);
        std::cerr << "Compute shader linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(computeShader);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name) const
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
        std::cerr << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;

    m_UniformLocationCache[name] = location;
    return location;
}

// Uniform uploads
void Shader::UploadUniformInt(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
{
    glUniform1iv(GetUniformLocation(name), count, values);
}

void Shader::UploadUniformFloat(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
{
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

// Public setter wrappers
void Shader::SetInt(const std::string& name, int value) { UploadUniformInt(name, value); }
void Shader::SetIntArray(const std::string& name, int* values, uint32_t count) { UploadUniformIntArray(name, values, count); }
void Shader::SetFloat(const std::string& name, float value) { UploadUniformFloat(name, value); }
void Shader::SetFloat3(const std::string& name, const glm::vec3& value) { UploadUniformFloat3(name, value); }
void Shader::SetFloat4(const std::string& name, const glm::vec4& value) { UploadUniformFloat4(name, value); }
void Shader::SetMat4(const std::string& name, const glm::mat4& value) { UploadUniformMat4(name, value); }

// Factory methods
std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
{
    // Determine type by extension or file content: default to combined vertex/fragment
    std::string source = ReadFile(filepath);
    // Simple split by markers could be implemented here, omitted for brevity
    // User should call specific overloads when needed
    return nullptr;
}

std::shared_ptr<Shader> Shader::Create(const std::string& name,
                                       const std::string& vertexSrc,
                                       const std::string& fragmentSrc)
{
    return std::make_shared<Shader>(name, vertexSrc, fragmentSrc);
}

std::shared_ptr<Shader> Shader::CreateCompute(const std::string& name,
                                              const std::string& computeSrc)
{
    return std::make_shared<Shader>(name, computeSrc);
}

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
    m_Shaders[shader->GetName()] = shader;
}

void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    m_Shaders[name] = shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
{
    // Loading logic could parse file into stages
    // Placeholder: user should manually provide sources
    return nullptr;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    return Load(filepath);
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
{
    if (!Exists(name))
        throw std::runtime_error("Shader not found: " + name);
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}
