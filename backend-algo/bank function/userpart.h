#include<iostream>
#include<vector>
#include<string>
using namespace std;
class User {
        int id;
        string userid;
        string username;
        string password;
        string salt;
        double balance;
    public:
        void loadDataFromFile();
        void registerFunc(string username,string password, double balance);
        void login(string inputusername,string inputpassword);
        void reloadLoginUser();
        void rewritetxt();
        vector<User> allUsers;
        class Bank{
            public:
            bool topupFunc(string selectedBank, double amount);
            void transfer(string inputuserid, double amount);
    };
        friend class Bank;
};
string hashPassword(const string& password, const string& salt);
string generateSalt(int len = 16);
vector<string> splitData(string rowData, char separator);
extern bool loginSuccess;
extern User loginUser;
extern int counter;