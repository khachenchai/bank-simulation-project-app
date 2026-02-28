#include "helper.h"
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QVector>
#include <QString>
#include <QDateTime>
#include <QCoreApplication>
#include <QDir>

bool Helper::checkIsNumerial(const QString& text) {
    bool isNumerial = false;
    text.toDouble(&isNumerial);
    return isNumerial;
}

QString Helper::hashPassword(const QString& password, const QString& salt) {
    QString combined = password + salt;
    QByteArray hash = QCryptographicHash::hash(combined.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString Helper::generateSalt(int len) {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        QString salt;
        QRandomGenerator* generator = QRandomGenerator::system();
        for (int i = 0; i < len; i++) {
            salt += charset[generator->bounded(sizeof(charset) - 1)];
        }
        return salt;
}

QString Helper::getDateTimeStr() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
}

QVector<QString> Helper::splitData(QString rowData, char seperator) {
    QString dataToAppend;
    QVector<QString> result;
    int count = 0;
    for (int i = 0; i < rowData.size(); i++) {
        if (rowData[i] == seperator) {
            result.push_back(dataToAppend);
            dataToAppend = "";
        } else dataToAppend += rowData[i];
    }
    result.push_back(dataToAppend);
    return result;
}



QString Helper::generateOTP() {
    QString otp;

    for (int i = 0; i < 6; ++i) {
        int digit = QRandomGenerator::global()->bounded(10); // 0–9
        otp.append(QString::number(digit));
    }

    return otp;
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
