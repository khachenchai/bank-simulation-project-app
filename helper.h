#ifndef HELPER_H
#define HELPER_H

#include <QVector>
#include <QString>

class Helper {
    public:
        static bool checkIsNumerial(const QString&);
        static QString hashPassword(const QString& password, const QString& salt);
        static QString generateSalt(int len = 16);
        static QVector<QString> splitData(QString rowData, char seperator);
        static QString getDateTimeStr();
};


#endif // HELPER_H
