#include"user.h"
#include "transaction.h"
#include "../helper.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QRandomGenerator>
#include <QDir>
// #include<random>
// #include<stdio.h>
// #include<iostream>
#include<QVector>
// #include<ctime>

void User::loadDataFromFile(){
    counter = 0;
    allUsers.clear();
    QFile readfile("../db/user.txt");
    if (!readfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file";
        return;
    }
    QTextStream in(&readfile);
    QString line;
    bool skipHeader = true;
    while (in.readLineInto(&line)){
        counter++;
        if (line == "" || line == "\r"){
            continue;
        }
        if (skipHeader) { skipHeader = false; continue; }
        QVector<QString> data = Helper::splitData(line,'|');
        User u;
        u.id = data[0].toInt();
        u.userid = data[1];
        u.username = data[2];
        u.password = data[3];
        u.salt = data[4];
        u.balance = data[5].toDouble();
        allUsers.push_back(u);
    }
    readfile.close();
}

bool Transaction::topupFunc(QString accId, QString selectedBank, double amount) {
    if (selectedBank != "Bank A" && selectedBank != "Bank B") {
        return false;
    }

    loginUser.balance += amount;
    
    User::reloadLoginUser();
    User::rewritetxt();
    return true;
}

QString Transaction::withdrawFunc(double amount) {
    if (amount > loginUser.balance) {
        return "";
    }
    QString otpStr = generateOTP();
    loginUser.balance -= amount;
    reloadLoginUser();
    rewritetxt();
    return otpStr.toStdString();
}

void Transaction::transfer(const QString& inputuserid, double amount)
{
    if (amount <= 0) {
        qWarning() << "Invalid amount";
        return;
    }

    User temp;
    temp.loadDataFromFile();

    // ---------- หา user ปลายทาง ----------
    int targetIndex = -1;
    for (int i = 0; i < temp.allUsers.size(); ++i) {
        if (temp.allUsers[i].userid == inputuserid) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        qWarning() << "Wrong Userid";
        return;
    }

    // ---------- เช็คเงิน ----------
    if (loginUser.balance < amount) {
        qWarning() << "Not enough money";
        return;
    }

    // ---------- ทำรายการ ----------
    temp.allUsers[targetIndex].balance += amount;
    loginUser.balance -= amount;

    temp.reloadLoginUser();
    temp.rewritetxt();

    // ---------- บันทึก transaction ----------
    QString path = "../db/transaction.txt";
    QFile file(path);

    int id = 0;

    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            in.readLine();
            ++id;
        }
        file.close();
    }

    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Cannot open transaction file";
        return;
    }

    QTextStream out(&file);

    QString dt = Helper::getDateTimeStr();

    out << id << '|'
        << dt << '|'
        << "transfer" << '|'
        << QString::number(amount, 'f', 2) << '|'
        << loginUser.userid << '|'
        << inputuserid
        << '\n';

    file.close();

    qDebug() << "Transfer success";
}
