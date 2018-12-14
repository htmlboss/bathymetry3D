#ifndef DIALOGSAVESCREENSHOT_H
#define DIALOGSAVESCREENSHOT_H

#include <QDialog>

namespace Ui {
class DialogSaveScreenshot;
}

class DialogSaveScreenshot : public QDialog {
Q_OBJECT

public:
    explicit DialogSaveScreenshot(const QImage& img, QWidget* parent = nullptr);
    ~DialogSaveScreenshot();

    auto getSaveFileName() const noexcept { return m_saveFileName; }

private slots:
    void on_pushButtonBrowse_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogSaveScreenshot* m_ui{ nullptr };

    QString m_saveFileName;
};

#endif // DIALOGSAVESCREENSHOT_H
