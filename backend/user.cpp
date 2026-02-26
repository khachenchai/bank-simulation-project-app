#include"user.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<random>
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
void User::registerFunc(QString username,QString password, double balance){
    bool skipHeader = true;
    User u;
    u.username=username;
    u.password=password;
    u.userid = QString::number(rand() % 900000 + 100000);
    for (int i = 0; i < allUsers.size(); i++) {
        if (allUsers[i].username == username) {
            qDebug() << "Username already exists!";
            return;
        }
    }
    for(int i=0;i<allUsers.size();i++){
        if(allUsers[i].userid == u.userid){
        u.userid = QString::number(rand() % 900000 + 100000);
        }
        else continue;
    }
    u.id = counter;
    QString salt = generateSalt();
    QString hash = hashPassword(password, salt);
    u.salt = salt;
    u.balance = balance;
    allUsers.push_back(u);
    QFile userFile("../db/user.txt");
    if (userFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&userFile);
        out << u.id << '|' << u.userid << '|' << u.username << '|' << hash << '|' << u.salt << '|' << u.balance << '\n';
        userFile.close();
    }
}

bool loginSuccess = false;
User loginUser;
void User::login(QString inputusername,QString inputpassword){
    loadDataFromFile();
    for (int i=0;i<allUsers.size();i++){
        if(allUsers[i].username == inputusername){
            QString hashPass = hashPassword(inputpassword,allUsers[i].salt);
            if(hashPass == allUsers[i].password){
                qDebug() << "Login susscess";
                loginSuccess = true;
                loginUser = allUsers[i];
                break;
            }
            else{
                qDebug() << "Wrong password";
                break;
            } 
        }
    }
}
void User::reloadLoginUser(){
    for(int i=0;i<allUsers.size();i++){
        if(allUsers[i].userid == loginUser.userid){
            allUsers[i] = loginUser;
            break;
        }
    }
}
void User::rewritetxt(){
    QFile outFile("../db/user.txt");
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&outFile);
        out << "id|userid|username|password|salt|balance\n";
        for (const auto& user : allUsers) {
            out << user.id << '|' << user.userid << '|' << user.username << '|' << user.password << '|' << user.salt << '|' << user.balance << '\n';
        }
        outFile.close();
    }
}
