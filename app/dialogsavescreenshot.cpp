#include "dialogsavescreenshot.h"
#include "ui_dialogsavescreenshot.h"

#include <QFileDialog>

/***********************************************************************************/
DialogSaveScreenshot::DialogSaveScreenshot(const QImage& img, QWidget *parent) : QDialog{parent},
                                                                                 m_ui{new Ui::DialogSaveScreenshot} {
    m_ui->setupUi(this);

    m_ui->screenshotPreview->setPixmap(QPixmap::fromImage(img));
}

/***********************************************************************************/
DialogSaveScreenshot::~DialogSaveScreenshot() {
    delete m_ui;
}

/***********************************************************************************/
void DialogSaveScreenshot::on_pushButtonBrowse_clicked() {
    const auto& filename{ QFileDialog::getSaveFileName(this,
                                                       tr("Save Screenshot"),
                                                       "",
                                                       tr("Images (*.png)")) };

    if (filename.isEmpty()) {
        return;
    }

    m_ui->lineEditFileName->setText(filename);
    m_saveFileName = filename;
}

/***********************************************************************************/
void DialogSaveScreenshot::on_buttonBox_accepted() {
    if (m_saveFileName.isEmpty()) {
        // do something for emtpy filename
    }
}
