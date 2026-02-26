#include "helper.h"
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QVector>
#include <QString>

bool Helper::checkIsNumerial(const QString& text)
{
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
            salt += charset[generator->bounded(0, sizeof(charset) - 1)];
        }
        return salt;
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



QString generateOTP()
{
    QString otp;

    for (int i = 0; i < 6; ++i) {
        int digit = QRandomGenerator::global()->bounded(10); // 0–9
        otp.append(QString::number(digit));
    }

    return otp;
}