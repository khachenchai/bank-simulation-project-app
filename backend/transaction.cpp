#include"user.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QRandomGenerator>
#include<random>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>

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
        vector<QString> data = splitData(line,'|');
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

bool User::Function::topupFunc(QString accId, QString selectedBank, double amount) {
    if (selectedBank != "Bank A" && selectedBank != "Bank B") {
        return false;
    }

    loginUser.balance += amount;
    
    User::reloadLoginUser();
    User::rewritetxt();
    return true;
}

QString User::Function::withdrawFunc(double amount) {
    if (amount > loginUser.balance) {
        return "";
    }
    QString otpStr = generateOTP();
    loginUser.balance -= amount;
    User::reloadLoginUser();
    User::rewritetxt();
    return otpStr;
}
