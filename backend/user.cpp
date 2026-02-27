#include"user.h"
#include "../helper.h"
#include<QFile>
#include<QTextStream>
#include<QDebug>
// #include<random>
#include <QVector>

User User::m_currentUser;
bool User::m_loginStatus = false;
QVector<User> allUsers;
int counter = 0;

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
        u.prefix = data[2];
        u.firstname = data[3];
        u.lastname = data[4];
        u.tel = data[5];
        u.ctzId = data[6];
        u.gender = data[7];
        u.password = data[8];
        u.salt = data[9];
        u.balance = data[10].toDouble();
        allUsers.push_back(u);
    }
    readfile.close();
}
bool User::registerFunc(QString prefix, QString firstname, QString lastname, QString tel, QString ctzId, QString gender, QString password, double balance){
    // bool skipHeader = true;

    for (int i = 0; i < allUsers.size(); i++) {
        if (allUsers[i].getCtzId() == ctzId) {
            qDebug() << "This Citizen ID already exists!";
            return false;
        }
    }

    int newId = allUsers.isEmpty() ? 1 : allUsers.last().getId() + 1;

    QString userId = QString::number(rand() % 900000 + 100000);
    bool isDuplicate;

    do {
        isDuplicate = false;
        userId = QString::number(rand() % 900000 + 100000);

        for (const User& user : std::as_const(allUsers)) {
            if (user.userid == userId) {
                isDuplicate = true;
                break;
            }
        }

    } while (isDuplicate);

    QString salt = Helper::generateSalt();
    QString hash = Helper::hashPassword(password, salt);

    User newUser(
        newId,
        userId,
        prefix,
        firstname,
        lastname,
        tel,
        ctzId,
        gender,
        hash,
        salt,
        balance
    );

    allUsers.push_back(newUser);

    QFile userFile("../db/user.txt");
    if (userFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&userFile);
        out << id << '|' << userid << '|' << prefix << '|' << firstname << '|' << lastname << '|' << tel << '|' << ctzId << '|' << gender << '|' << hash << '|' << salt << '|' << balance << '\n';
        userFile.close();
    }

    return true;
}

bool User::verifyPassword(const QString& inputPassword) {
    QString hashPass = Helper::hashPassword(inputPassword, salt);
    return hashPass == password;
}

bool User::login(QString inputCtzId, QString inputPassword){
    loadDataFromFile();
    for (int i=0;i<allUsers.size();i++){
        if(allUsers[i].getCtzId() == inputCtzId){
            if(allUsers[i].verifyPassword(inputPassword)){
                qDebug() << "Login susscess";
                // session logic here
                m_currentUser = allUsers[i];
                m_loginStatus = true;
                return true;
            }
            else{
                qDebug() << "Wrong password";
                return false;
            } 
        }
    }
    qDebug() << "User not found";
    return false;
}

// void User::reloadLoginUser(){
//     for(int i=0;i<allUsers.size();i++){
//         if(allUsers[i].userid == loginUser.userid){
//             allUsers[i] = loginUser;
//             break;
//         }
//     }
// }
void User::rewritetxt(){
    QFile outFile("../db/user.txt");
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&outFile);
        out << "id|userid|prefix|firstname|lastname|tel|ctzId|gender|password|salt|balance\n";
        for (const auto& user : std::as_const(allUsers)) {
            out << user.id << '|' << user.userid << '|' << user.prefix << '|' << user.firstname << '|' << user.lastname << '|' << user.tel << '|' << user.ctzId << '|' << user.gender << '|' << user.password << '|' << user.salt << '|' << user.balance << '\n';
        }
        outFile.close();
    }
}
