#include <QVector>
#include <QString>
class User {
        int id;
        QString userid;
        QString username;
        QString password;
        QString salt;
        double balance;
    public:
        void loadDataFromFile();
        void registerFunc(QString username,QString password, double balance);
        void login(QString inputusername,QString inputpassword);
        void reloadLoginUser();
        void rewritetxt();
        
        QVector<User> allUsers;
        class  Function {
            public:
            bool topupFunc(QString selectedBank, double amount);
            QString withdrawFunc(double amount);
        };
        friend class Function;
};
QString hashPassword(const QString& password, const QString& salt);
QString generateSalt(int len = 16);
QVector<QString> splitData(QString rowData, char separator);
QString generateOTP();
extern bool loginSuccess;
extern User loginUser;
extern int counter;
