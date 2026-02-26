#ifndef USERPART_H
#define USERPART_H

#include <string>
#include <vector>

struct User {
    int id;
    std::string userid;
    std::string username;
    std::string password;
    std::string salt;
    double balance;
};

// global storage
extern std::vector<User> allUsers;
extern User loginUser;
extern bool loginSuccess;

// function declarations
void loadDataFromFile();
void registerFunc(std::string username, std::string password, double balance);
void login(std::string inputusername, std::string inputpassword);

#endif // USERPART_H
