#ifndef HELPER_H
#define HELPER_H

#include <qcontainerfwd.h>
#include <vector>
#include <QString>

class Helper {
    public:
        static bool checkIsNumerial(const QString&);
};

// bool Helper::checkIsNumerial(const QString &text) {
//     bool isNumerial = false;
//     text.toDouble(&isNumerial);
//     return isNumerial;
// }

#endif // HELPER_H
