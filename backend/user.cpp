#include"user.h"
#include "../helper.h"
#include<QFile>
#include <QDir>
#include<QTextStream>
#include<QDebug>
// #include<random>
#include <QVector>
#include <QCoreApplication>

User User::m_currentUser;
bool User::m_loginStatus = false;
QVector<User> User::allUsers;
int counter = 0;

User::User(int id,
           const QString& userid,
           const QString& prefix,
           const QString& firstname,
           const QString& lastname,
           const QString& tel,
           const QString& ctzId,
           const QString& gender,
           const QString& password,
           const QString& salt,
           double balance)
{
    this->id = id;
    this->userid = userid;
    this->prefix = prefix;
    this->firstname = firstname;
    this->lastname = lastname;
    this->tel = tel;
    this->ctzId = ctzId;
    this->gender = gender;
    this->password = password;
    this->salt = salt;
    this->balance = balance;
}

void User::loadDataFromFile(){
    counter = 0;
    allUsers.clear();
    qDebug() << QDir::currentPath();
    QFile readfile(Helper::getUserDBPath());
    if (!readfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open file";
        return;
    }
    QTextStream in(&readfile);
    QString line;
    bool skipHeader = true;
    while (in.readLineInto(&line)){

        line = line.trimmed();
        qDebug() << line;

        if (line.isEmpty()) continue;
        if (skipHeader) { skipHeader = false; continue; }

        QStringList data = line.split('|');

        if (data.size() < 11) {
            qDebug() << "Invalid row:" << line;
            continue;
        }

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

        qDebug() << "Loaded ctzId:" << u.ctzId;

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

    QString userId = QString::number(rand() % 90000000 + 10000000);
    bool isDuplicate;

    do {
        isDuplicate = false;
        userId = QString::number(rand() % 90000000 + 10000000);

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

    QString basePath = QCoreApplication::applicationDirPath();
    QString dbPath = basePath;

    QDir dir;
    if (!dir.exists(dbPath)) {
        dir.mkpath(dbPath);
    }

    QString filePath = dbPath + "/../../db/user.txt";

    QFile userFile(filePath);
    qDebug() << QDir::currentPath();
    qDebug() << filePath;

    if (!userFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << userFile.errorString();
        return false;
    }

    QTextStream out(&userFile);
    out << newId << '|' << userId << '|' << prefix << '|' << firstname << '|' << lastname << '|' << tel << '|' << ctzId << '|' << gender << '|' << hash << '|' << salt << '|' << balance << '\n';
    userFile.close();

    return true;
}

bool User::verifyPassword(const QString& inputPassword, const QString& salt) {
    QString hashPass = Helper::hashPassword(inputPassword, salt);
    return hashPass == password;
}

bool User::login(QString inputCtzId, QString inputPassword){
    m_loginStatus = false;
    loadDataFromFile();
    for (int i=0;i<allUsers.size();i++){
        qDebug() << allUsers[i].getCtzId();
        if(allUsers[i].getCtzId() == inputCtzId){
            if(allUsers[i].verifyPassword(inputPassword, allUsers[i].salt)){
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
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot rewrite user.txt";
        return;
    }

    QTextStream out(&outFile);

    out << "id|userid|prefix|firstname|lastname|tel|ctzId|gender|password|salt|balance\n";

    for (const auto& user : std::as_const(allUsers)) {
        out << user.getId() << '|'
            << user.getUserId() << '|'
            << user.prefix << '|'
            << user.firstname << '|'
            << user.lastname << '|'
            << user.tel << '|'
            << user.getCtzId() << '|'
            << user.gender << '|'
            << user.password << '|'
            << user.salt << '|'
            << user.getBalance()
            << '\n';


    }
    outFile.close();
}

bool User::isLoggedIn() {
    return m_loginStatus;
}

User& User::currentUser() {
    return m_currentUser;
}

int User::findUserIndexByUserId(const QString& userId) {
    for (int i = 0; i < allUsers.size(); ++i) {
        if (allUsers[i].getUserId() == userId)
            return i;
    }
    return -1;
}

int User::findCurrentUserIndex() {
    return findUserIndexByUserId(m_currentUser.getUserId());
}

void User::updateBalance(int index, double newBalance) {
    if (index >= 0 && index < allUsers.size()) {
        allUsers[index].setBalance(newBalance);

        if (allUsers[index].getUserId() ==
            m_currentUser.getUserId()) {
            m_currentUser = allUsers[index];
        }
    }
}

double User::getBalanceByIndex(int index) {
    if (index >= 0 && index < allUsers.size())
        return allUsers[index].getBalance();

    return 0;
}

void User::addBalance(int index, double amount) {
    if (index >= 0 && index < allUsers.size()) {

        double newBalance =
            allUsers[index].getBalance() + amount;

        allUsers[index].setBalance(newBalance);

        // sync session ถ้าเป็น user ที่ login อยู่
        if (allUsers[index].getUserId() ==
            m_currentUser.getUserId()) {
            m_currentUser = allUsers[index];
        }
    }
}
