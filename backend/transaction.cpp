#include"user.h"
#include "transaction.h"
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

bool User::Bank::topupFunc(QString accId, QString selectedBank, double amount) {
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

void Transaction::transfer(QString inputuserid, double amount){

    User temp;
    temp.loadDataFromFile();
    bool check = false, isAffort = true;
    for (int i=0;i<temp.allUsers.size();i++){
        if(temp.allUsers[i].userid == inputuserid){
            check = true;
            if(loginUser.balance < amount){
                // cout << "Not enough money\n"
                isAffort = false;
                break;
            }
            else{
                temp.allUsers[i].balance += amount;
                loginUser.balance -= amount;
                temp.reloadLoginUser();
                temp.rewritetxt();
                break;
            }
        }
    }
    if(!check){
        cout << "Wrong Userid\n";
    } else if (!isAffort) cout << "Not enough money"; 
    else {
        ifstream transactionFile("../database/demo_transaction.txt");

        string line;
        int counter = 0;
        while (getline(transactionFile,line)){
            counter++;
        }

        transactionFile.close();
        ofstream transactionFileOut("../database/demo_transaction.txt", ios::app);
        int id = counter;
        string dt = getDateTimeStr();

        transactionFileOut << id << '|' << dt << '|' << "transfer" << '|' << amount << '|' << loginUser.userid << '|' << inputuserid << endl;

        transactionFileOut.close();
    }
}