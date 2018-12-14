#include "gpuprogram.h"

#include "shader.h"

#include <glm/gtc/type_ptr.hpp>

#include <array>

#include <QOpenGLFunctions_4_4_Core>

#ifdef QT_DEBUG
    #include <QDebug>
#endif

/***********************************************************************************/
GPUProgram::GPUProgram(const std::string_view programName,
                       const std::initializer_list<Shader>& shaders,
                       QOpenGLFunctions_4_4_Core* funcs) :  m_programName{ programName },
                                                            m_funcs{ funcs } {

    Q_ASSERT(m_ID == 0);

    m_ID = m_funcs->glCreateProgram();

    for (const auto& shader : shaders) {
        m_funcs->glAttachShader(m_ID, shader.m_ID);
    }

    if (linkAndValidate()) {
        getUniforms();
    }

    // Cleanup
    for (auto shader : shaders) {
        m_funcs->glDetachShader(m_ID, shader.m_ID);
        shader.Delete();
    }
}

/***********************************************************************************/
GPUProgram::~GPUProgram() {
    Delete();
}

/***********************************************************************************/
void GPUProgram::Delete() {
    if (m_ID != 0) {
        m_funcs->glDeleteProgram(m_ID);
        m_ID = 0;
        m_funcs = nullptr;
#ifdef QT_DEBUG
        qDebug() << "GPU Program deleted: " << m_programName.data();
#endif
    }

    Q_ASSERT(m_ID == 0);
    Q_ASSERT(m_funcs == nullptr);
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const int value) {
    m_funcs->glProgramUniform1i(m_ID, m_uniforms.at(uniformName), value);

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const float value) {
    m_funcs->glProgramUniform1f(m_ID, m_uniforms.at(uniformName), value);

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const glm::ivec2& value) {
    m_funcs->glProgramUniform2iv(m_ID, m_uniforms.at(uniformName), 1, glm::value_ptr(value));

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const glm::vec2& value) {
    m_funcs->glProgramUniform2fv(m_ID, m_uniforms.at(uniformName), 1, glm::value_ptr(value));

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const glm::vec3& value) {
    m_funcs->glProgramUniform3fv(m_ID, m_uniforms.at(uniformName), 1, glm::value_ptr(value));

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const glm::vec4& value) {
    m_funcs->glProgramUniform4fv(m_ID, m_uniforms.at(uniformName), 1, glm::value_ptr(value));

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const glm::mat3x3& value) {
    m_funcs->glProgramUniformMatrix3fv(m_ID, m_uniforms.at(uniformName), 1, GL_FALSE, glm::value_ptr(value));

    return *this;
}

/***********************************************************************************/
GPUProgram& GPUProgram::SetUniform(const std::string& uniformName, const glm::mat4x4& value) {
    m_funcs->glProgramUniformMatrix4fv(m_ID, m_uniforms.at(uniformName), 1, GL_FALSE, glm::value_ptr(value));

    return *this;
}

/***********************************************************************************/
bool GPUProgram::linkAndValidate() {
    int success{ -1 };
    std::array<char, 1024> infoLog;

    m_funcs->glLinkProgram(m_ID);
    m_funcs->glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        m_funcs->glGetProgramInfoLog(m_ID, infoLog.size(), nullptr, infoLog.data());
#ifdef QT_DEBUG
        qDebug() << m_programName.data() << " linking error: " << infoLog.data();
#endif
        return false;
    }

    m_funcs->glValidateProgram(m_ID);
    m_funcs->glGetProgramiv(m_ID, GL_VALIDATE_STATUS, &success);
    if (!success) {
        m_funcs->glGetProgramInfoLog(m_ID, infoLog.size(), nullptr, infoLog.data());
#ifdef QT_DEBUG
        qDebug() << m_programName.data() << " validation error: " << infoLog.data();
#endif
        return false;
    }

#ifdef QT_DEBUG
    qDebug() << "GPU Program compiled: " << m_programName.data();
#endif

    return true;
}

/***********************************************************************************/
void GPUProgram::getUniforms() {
    int total{ -1 };
    m_funcs->glGetProgramiv(m_ID, GL_ACTIVE_UNIFORMS, &total);

    for (auto i = 0; i < total; ++i) {
        int name_len{ -1 }, num{ -1 };
        GLenum type{ GL_ZERO };
        char name[100];
        m_funcs->glGetActiveUniform(m_ID, static_cast<GLuint>(i), sizeof(name) - 1, &name_len, &num, &type, name);
        name[name_len] = 0;

        const std::string nameStr{ name };

        m_uniforms.try_emplace(nameStr, m_funcs->glGetUniformLocation(m_ID, name));
    }
}
