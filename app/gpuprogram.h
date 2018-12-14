#ifndef GPUPROGRAM_H
#define GPUPROGRAM_H

#include <glm/mat4x4.hpp>

#include <string>
#include <unordered_map>

#include <QOpenGLFunctions_4_4_Core>

/***********************************************************************************/
// Forward declarations
class Shader;

/***********************************************************************************/
class GPUProgram {

public:
    GPUProgram(const std::string_view programName, const std::initializer_list<Shader>& shaders, QOpenGLFunctions_4_4_Core* funcs);
    ~GPUProgram();

    GPUProgram(const GPUProgram&) = delete;
    GPUProgram(GPUProgram&&) = default;
    GPUProgram& operator=(const GPUProgram&) = delete;
    GPUProgram& operator=(GPUProgram&&) = default;

    void Delete();

    auto GetName() const noexcept { return m_programName; }

    GPUProgram& SetUniform(const std::string& uniformName, const int value);
    GPUProgram& SetUniform(const std::string& uniformName, const float value);
    GPUProgram& SetUniform(const std::string& uniformName, const glm::ivec2& value);
    GPUProgram& SetUniform(const std::string& uniformName, const glm::vec2& value);
    GPUProgram& SetUniform(const std::string& uniformName, const glm::vec3& value);
    GPUProgram& SetUniform(const std::string& uniformName, const glm::vec4& value);
    GPUProgram& SetUniform(const std::string& uniformName, const glm::mat3x3& value);
    GPUProgram& SetUniform(const std::string& uniformName, const glm::mat4x4& value);

private:
    ///
    [[nodiscard]] bool linkAndValidate();
    ///
    void getUniforms();

    std::string m_programName;
    GLuint m_ID{ 0 };

    std::unordered_map<std::string, GLint> m_uniforms;

    QOpenGLFunctions_4_4_Core* m_funcs{ nullptr };
};

#endif // GPUPROGRAM_H
