#include <QString>

class Transaction {
    public:
        bool topupFunc(QString bankName, double amount);
        QString withdrawFunc(double amount);
        bool transferFunc(const QString& inputuserid, QString toBank, double amount);
};
