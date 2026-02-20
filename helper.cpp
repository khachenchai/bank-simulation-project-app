#include "helper.h"

bool Helper::checkIsNumerial(const QString& text)
{
    bool isNumerial = false;
    text.toDouble(&isNumerial);
    return isNumerial;
}
