#include <QString>

struct TransactionRecord {
    int id;
    QString dateTime;
    QString type;
    double amount;
    QString fromBank;
    QString toBank;
    QString fromId;
    QString toId;
};

class Transaction {
    public:
        bool topupFunc(QString bankName, double amount);
        QString withdrawFunc(double amount);
        bool transferFunc(const QString& inputuserid, QString toBank, double amount);
        QVector<TransactionRecord> getMyTransactions();
};
