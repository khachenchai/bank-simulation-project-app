#ifndef HELPER_H
#define HELPER_H

#include <qcontainerfwd.h>
#include <QString>

class Helper {
    public:
        static bool checkIsNumerial(const QString&);
        static QString getUserDBPath();
        static QString getTransactionDBPath();
};

// bool Helper::checkIsNumerial(const QString &text) {
//     bool isNumerial = false;
//     text.toDouble(&isNumerial);
//     return isNumerial;
// }

#endif // HELPER_H
