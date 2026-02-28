#ifndef USER_H
#define USER_H

#include <QVector>
#include <QString>
class User {
    private:
        int id;
        QString userid;
        QString prefix;
        QString firstname;
        QString lastname;
        QString tel;
        QString ctzId;
        QString gender;
        QString password;
        QString salt;
        double balance;
    public:
        User() = default;
        User(int id,
             const QString& userid,
             const QString& prefix,
             const QString& firstname,
             const QString& lastname,
             const QString& tel,
             const QString& ctzId,
             const QString& gender,
             const QString& password,
             const QString& salt,
             double balance);

        static void loadDataFromFile();
        bool registerFunc(QString prefix, QString firstname, QString lastname, QString tel, QString ctzId, QString gender, QString password, double balance);
        bool login(QString inputusername,QString inputpassword);
        bool verifyPassword(const QString& inputPassword);
        static void rewritetxt();
        QString withdrawFunc(double amount);
        static int findUserIndexByUserId(const QString& userId);
        static int findCurrentUserIndex();
        static double getBalanceByIndex(int index);
        static void addBalance(int index, double amount);

        // -- Getter Func --
        int getId() const {return id;}
        QString getUserId() const {return userid;}
        QString getFullname() const {return prefix+firstname+' '+lastname;}
        QString getFirstname() const {return firstname;}
        QString getTel() const {return tel;}
        QString getGender() const {return gender;}
        QString getCtzId() const {return ctzId;}
        double getBalance() const {return balance;}
        static void updateBalance(int index, double newBalance);

        void setBalance(double b) {balance = b;}

        // -- session
        static User& currentUser();
        static bool isLoggedIn();
        static void logout();

    private:
        static User m_currentUser;
        static bool m_loginStatus;
        static QVector<User> allUsers;

        // class Func {
        //     public:
        //     bool topupFunc(QString selectedBank, double amount);
        // };
        // friend class Func;
};


#endif
