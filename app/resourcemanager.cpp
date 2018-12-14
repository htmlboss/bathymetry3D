#include "resourcemanager.h"

#include <QFile>

/***********************************************************************************/
QString ResourceManager::LoadTextFile(const QString& path, const bool strip) const {

    Q_ASSERT(QFile::exists(path));

    QFile f{ path };
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        //qDebug() << "Failed to open: " << path;
        return {};
    }

    const QString& text{ f.readAll() };

    if (strip) {
        return text.simplified();
    }

    return text;
}
