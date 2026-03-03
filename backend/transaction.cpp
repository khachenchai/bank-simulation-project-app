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

    // User::loadDataFromFile();

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
        << User::currentUser().getUserId() << '|'
        << '\n';

    file.close();

    qDebug() << "Transfer success";

    return true;
}

// ต้องแก้
QString Transaction::withdrawFunc(double amount)
{
    if (!User::isLoggedIn()) return "";

    if (amount <= 0) return "";

    User::loadDataFromFile();

    int index = User::findCurrentUserIndex();
    if (index == -1) return "";

    double currentBalance =
        User::currentUser().getBalance();

    if (amount > currentBalance) return "";

    QString otpStr = Helper::generateOTP();

    double newBalance = currentBalance - amount;

    User::updateBalance(index, newBalance);

    User::rewritetxt();

    return otpStr;
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

    User::loadDataFromFile();

    int senderIndex = User::findCurrentUserIndex();
    int targetIndex = User::findUserIndexByUserId(inputuserid);

    if (senderIndex == -1) {
        qWarning() << "Sender not found";
        return false;
    }

    if (targetIndex == -1) {
        qWarning() << "Wrong Userid";
        return false;
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

    out << id << '|'
        << dt << '|'
        << "transfer" << '|'
        << QString::number(amount, 'f', 2) << '|'
        << User::currentUser().getUserId() << '|'
        << inputuserid
        << '\n';

    file.close();

    qDebug() << "Transfer success";
    return true;
}
