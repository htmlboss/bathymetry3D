#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_4_Core>

#include "camera.h"
#include "timer.h"
#include "gpuprogram.h"

/***********************************************************************************/
class OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT
public:

    OpenGLWidget(QWidget* parent = nullptr);
    ~OpenGLWidget() override;

protected slots:
    void update();

protected:
    // Rendering
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // Input events
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void shutdownGL();
    void compileShaders();

    QOpenGLFunctions_4_4_Core m_funcs;

    Timer m_timer;
    Camera m_camera;

    std::unordered_map<std::string, GPUProgram> m_shaderCache;
};

#endif // OPENGLWIDGET_H
