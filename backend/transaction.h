#include <QString>

class Transaction {
    public:
        bool topupFunc(QString bankName, double amount);
        QString withdrawFunc(double amount);
        void transfer(const QString& inputuserid, double amount);
};
