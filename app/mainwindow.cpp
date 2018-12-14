#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogsavescreenshot.h"

#include <QMessageBox>

/***********************************************************************************/
MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent}, m_ui{new Ui::MainWindow} {
    m_ui->setupUi(this);
}

/***********************************************************************************/
MainWindow::~MainWindow() {
    delete m_ui;
}

/***********************************************************************************/
void MainWindow::on_actionAbout_Qt_triggered() {
    QMessageBox::aboutQt(this);
}

/***********************************************************************************/
void MainWindow::showStatusBarMessage(const QString& message) {
    statusBar()->showMessage(message, 5000);
}

/***********************************************************************************/
void MainWindow::on_actionClose_triggered() {
    close();
}

/***********************************************************************************/
void MainWindow::on_actionScreenshot_triggered() {
    const auto& img{ m_ui->openGLWidget->grabFramebuffer() };

    DialogSaveScreenshot dlg{img, this};

    if (dlg.exec()) {
        img.save(dlg.getSaveFileName());

        statusBar()->showMessage(tr("Screenshot saved to: ") + dlg.getSaveFileName());
    }
}
