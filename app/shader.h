#ifndef GLSHADER_H
#define GLSHADER_H

#include <QOpenGLFunctions_4_4_Core>

#include <filesystem>
#include <string_view>

/***********************************************************************************/
// Forward declarations
class GPUProgram;

/***********************************************************************************/
class Shader {
    friend class GPUProgram;
public:
    enum Type : decltype(GL_VERTEX_SHADER) {
        VERTEX = GL_VERTEX_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        COMPUTE = GL_COMPUTE_SHADER,
        TESS_CONTROL = GL_TESS_CONTROL_SHADER,
        TESS_EVAL = GL_TESS_EVALUATION_SHADER
    };

    Shader(const QString& shaderCode, const Type type, QOpenGLFunctions_4_4_Core* funcs);
    ~Shader();

    Shader(const Shader&) = default;
    Shader(Shader&&) = default;
    Shader& operator=(const Shader&) = default;
    Shader& operator=(Shader&&) = default;

    void Delete();


private:
    /// Replaces all occurances of a string in another string
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
    /// Compiles a shader file and checks for errors
    void compile(const GLchar* shaderCode);

    GLuint m_ID{ 0 };

    QOpenGLFunctions_4_4_Core* m_funcs{ nullptr };
};

#endif // GLSHADER_H
