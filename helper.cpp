#include "helper.h"
#include <QCoreApplication>
#include <QDir>

bool Helper::checkIsNumerial(const QString& text)
{
    bool isNumerial = false;
    text.toDouble(&isNumerial);
    return isNumerial;
}

QString Helper::getUserDBPath() {
    QString basePath = QCoreApplication::applicationDirPath();
    QString dbPath = basePath;

    QDir dir;
    if (!dir.exists(dbPath)) {
        dir.mkpath(dbPath);
    }

    QString filePath = dbPath + "/../../db/user.txt";
    return filePath;
}

QString Helper::getTransactionDBPath() {
    QString basePath = QCoreApplication::applicationDirPath();
    QString dbPath = basePath;

    QDir dir;
    if (!dir.exists(dbPath)) {
        dir.mkpath(dbPath);
    }

    QString filePath = dbPath + "/../../db/transaction.txt";
    return filePath;
}
