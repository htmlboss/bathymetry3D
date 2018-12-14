#include "openglwidget.h"

#include "inputmanager.h"
#include "resourcemanager.h"
#include "shader.h"

#include <QKeyEvent>

#include <exception>

#ifdef QT_DEBUG
    #include <QDebug>
#endif

/***********************************************************************************/
OpenGLWidget::OpenGLWidget(QWidget* parent) : QOpenGLWidget{parent} {

}

/***********************************************************************************/
OpenGLWidget::~OpenGLWidget() {
    makeCurrent();
    shutdownGL();
}

/***********************************************************************************/
void OpenGLWidget::update() {
    m_timer.update();

    InputManager::update();

    // Update camera when right mouse button is held down
    if (InputManager::buttonPressed(Qt::RightButton)) {

        m_camera.Update(m_timer.getDelta());
    }

    QOpenGLWidget::update();
}

/***********************************************************************************/
void OpenGLWidget::initializeGL() {
    if (!m_funcs.initializeOpenGLFunctions()) {
#ifdef QT_DEBUG
        qDebug() << "Failed to intialize OpenGL 4.4 Core functions.";
#endif
        throw std::runtime_error("");
    };

    makeCurrent();

    QObject::connect(this, &QOpenGLWidget::frameSwapped, this, &OpenGLWidget::update);

    m_funcs.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    m_funcs.glEnable(GL_DEPTH_TEST);

    compileShaders();
}

/***********************************************************************************/
void OpenGLWidget::resizeGL(int w, int h) {
    m_funcs.glViewport(0, 0, w, h);
}

/***********************************************************************************/
void OpenGLWidget::paintGL() {
    m_funcs.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/***********************************************************************************/
void OpenGLWidget::keyPressEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        event->ignore();
    }
    else {
        InputManager::registerKeyPress(event->key());
    }
}

/***********************************************************************************/
void OpenGLWidget::keyReleaseEvent(QKeyEvent* event) {
    if (event->isAutoRepeat()) {
        event->ignore();
    }
    else {
        InputManager::registerKeyRelease(event->key());
    }
}

/***********************************************************************************/
void OpenGLWidget::mousePressEvent(QMouseEvent* event) {
    InputManager::registerMousePress(event->button());
}

/***********************************************************************************/
void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event) {
    InputManager::registerMouseRelease(event->button());
}

/***********************************************************************************/
void OpenGLWidget::shutdownGL() {
    for (auto& shader : m_shaderCache) {
        shader.second.Delete();
    }
}

/***********************************************************************************/
void OpenGLWidget::compileShaders() {
    const auto& basicShaderVSCode{ ResourceManager::GetInstance().LoadTextFile(QStringLiteral(":/shaders/shaders/basic.vert")) };
    Shader basicShaderVS{ basicShaderVSCode, Shader::Type::VERTEX, std::addressof(m_funcs) };

    const auto& basicShaderFSCode{ ResourceManager::GetInstance().LoadTextFile(QStringLiteral(":/shaders/shaders/basic.frag")) };
    Shader basicShaderFS{ basicShaderFSCode, Shader::Type::FRAGMENT, std::addressof(m_funcs) };

    m_shaderCache.try_emplace("Basic Shader", GPUProgram("Basic Shader", { basicShaderVS, basicShaderFS }, std::addressof(m_funcs)));
}
