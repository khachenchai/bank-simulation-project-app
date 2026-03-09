#include"user.h"
#include "transaction.h"
#include "../helper.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QRandomGenerator>
#include <QDir>
#include<QVector>

bool Transaction::topupFunc(QString selectedBank, double amount)
{
    if (!User::isLoggedIn())
        return false;

    int index = User::findCurrentUserIndex();
    if (index == -1)
        return false;

    double newBalance =
        User::currentUser().getBalance() + amount;

    User::updateBalance(index, newBalance);

    User::rewritetxt();

    // ===== บันทึก transaction =====
    QString path = Helper::getTransactionDBPath();
    QFile file(path);

    int id = 0;

    if (file.exists() &&
        file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QTextStream in(&file);
        while (!in.atEnd()) {
            in.readLine();
            ++id;
        }
        file.close();
    }

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Cannot open transaction file";
        return false;
    }





    QTextStream out(&file);
    QString dt = Helper::getDateTimeStr();
    QString userId = User::currentUser().getUserId();

    out << id << '|'
        << dt << '|'
        << "topup" << '|'
        << QString::number(amount, 'f', 2) << '|'
        << selectedBank << '|'
        << "Mhee Bank" << "||"
        << userId
        << '\n';

    file.close();

    qDebug() << "Transfer success";

    return true;
}

// ต้องแก้
bool Transaction::withdrawFunc(double amount)
{
    if (!User::isLoggedIn()) return false;

    if (amount <= 0) return false;

    int index = User::findCurrentUserIndex();
    if (index == -1) return false;

    double currentBalance =
        User::currentUser().getBalance();

    if (amount > currentBalance) return false;

    double newBalance = currentBalance - amount;

    User::updateBalance(index, newBalance);

    User::rewritetxt();

    // ===== บันทึก transaction =====
    QString path = Helper::getTransactionDBPath();
    QFile file(path);

    int id = 0;

    if (file.exists() &&
        file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QTextStream in(&file);
        while (!in.atEnd()) {
            in.readLine();
            ++id;
        }
        file.close();
    }

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Cannot open transaction file";
        return false;
    }



    QTextStream out(&file);
    QString dt = Helper::getDateTimeStr();
    QString userId = User::currentUser().getUserId();

    out << id << '|'
        << dt << '|'
        << "withdraw" << '|'
        << QString::number(amount, 'f', 2) << '|'
        << "Mhee Bank" << '|'
        << "" << "|"
        << userId << '|'
        << '\n';

    file.close();

    qDebug() << "Withdraw success";

    return true;
}

bool Transaction::transferFunc(const QString& inputuserid, QString toBank, double amount) {

    if (!User::isLoggedIn()) {
        qWarning() << "Not logged in";
        return false;
    }

    if (amount <= 0) {
        qWarning() << "Invalid amount";
        return false;
    }

    int senderIndex = User::findCurrentUserIndex();
    int targetIndex = -1;

    if (senderIndex == -1) {
        qWarning() << "Sender not found";
        return false;
    }

    if (toBank == "Mhee Bank") {
        targetIndex = User::findUserIndexByUserId(inputuserid);
        if (targetIndex == -1) {
            qWarning() << "Wrong Userid";
            return false;
        }
    }

    double senderBalance = User::currentUser().getBalance();

    if (senderBalance < amount) {
        qWarning() << "Not enough money";
        return false;
    }

    // ===== ทำรายการ =====
    if (toBank == "Mhee Bank") {
        double newSenderBalance = senderBalance - amount;
        double newTargetBalance =
            User::getBalanceByIndex(targetIndex) + amount;

        User::updateBalance(senderIndex, newSenderBalance);
        User::updateBalance(targetIndex, newTargetBalance);

        User::rewritetxt();
    } else {
        double newSenderBalance = senderBalance - amount;

        User::updateBalance(senderIndex, newSenderBalance);

        User::rewritetxt();
    }

    // ===== บันทึก transaction =====
    QString path = Helper::getTransactionDBPath();
    QFile file(path);

    int id = 0;

    if (file.exists() &&
        file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QTextStream in(&file);
        while (!in.atEnd()) {
            in.readLine();
            ++id;
        }
        file.close();
    }

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Cannot open transaction file";
        return false;
    }

    QTextStream out(&file);
    QString dt = Helper::getDateTimeStr();
    QString userId = User::currentUser().getUserId();

    out << id << '|'
        << dt << '|'
        << "transfer" << '|'
        << QString::number(amount, 'f', 2) << '|'
        << "Mhee Bank" << '|'
        << toBank << '|'
        << userId << '|'
        << inputuserid
        << '\n';

    file.close();

    qDebug() << "Transfer success";
    return true;
}

QVector<TransactionRecord> Transaction::getMyTransactions() {
    QVector<TransactionRecord> myTransactions;

    if (!User::isLoggedIn())
        return myTransactions;

    QString currentUserId =
        User::currentUser().getUserId();

    QFile file(Helper::getTransactionDBPath());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open transaction file";
        return myTransactions;
    }

    QTextStream in(&file);

    bool skipHeader = true;

    while (!in.atEnd()) {

        QString line = in.readLine().trimmed();

        if (line.isEmpty())
            continue;

        if (skipHeader) {
            skipHeader = false;
            continue;
        }

        QStringList data = line.split('|');

        if (data.size() < 8)
            continue;

        QString fromId = data[6];
        QString toId   = data[7];

        if (fromId == currentUserId ||
            toId == currentUserId) {

            TransactionRecord record;

            record.id        = data[0].toInt();
            record.dateTime  = data[1];
            record.type      = data[2];
            record.amount    = data[3].toDouble();
            record.fromBank  = data[4];
            record.toBank    = data[5];
            record.fromId    = fromId;
            record.toId      = toId;

            myTransactions.push_front(record);
        }
    }

    file.close();

    return myTransactions;
}
