#include "shader.h"

#include "resourcemanager.h"

#include <array>

#ifdef QT_DEBUG
#include <QDebug>
#endif

/***********************************************************************************/
Shader::Shader(const QString& shaderCode,
               const Type type,
               QOpenGLFunctions_4_4_Core* funcs) : m_funcs{ funcs } {

    Q_ASSERT(m_ID == 0);

    m_ID = m_funcs->glCreateShader(type);

    compile(shaderCode.toStdString().c_str());
}

/***********************************************************************************/
Shader::~Shader() {
    Delete();
}

/***********************************************************************************/
void Shader::Delete() {
    if (m_ID != 0) {
        m_funcs->glDeleteShader(m_ID);
        m_ID = 0;
        m_funcs = nullptr;
    }

    Q_ASSERT(m_ID == 0);
    Q_ASSERT(m_funcs == nullptr);
}

/***********************************************************************************/
void Shader::replaceAll(std::string& str, const std::string& from, const std::string& to) {
    std::size_t start_pos{ 0 };

    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

/***********************************************************************************/
void Shader::compile(const GLchar* shaderCode) {

    Q_ASSERT(shaderCode != nullptr);

    GLint m_success{ 0 };
    std::array<GLchar, 1024> infoLog;

    m_funcs->glShaderSource(m_ID, 1, &shaderCode, nullptr);
    m_funcs->glCompileShader(m_ID);

    m_funcs->glGetShaderiv(m_ID, GL_COMPILE_STATUS, &m_success);
    if (!m_success) {
        m_funcs->glGetShaderInfoLog(m_ID, infoLog.size(), nullptr, infoLog.data());
#ifdef QT_DEBUG
        qCritical() << infoLog.data();
#endif
    }
}
