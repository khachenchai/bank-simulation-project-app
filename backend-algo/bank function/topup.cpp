#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
using namespace std;
struct User {
    int id;
    string userid;
    string username;
    string password;
    string salt;
    double balance;
};

struct Bank{
    string name;
    double balance;
};

extern vector<User> allUsers;
extern User loginUser;
extern bool loginSuccess;
extern void loadDataFromFile();
extern void registerFunc(string username, string password, double balance);
extern void login(string inputusername, string inputpassword);

// Topup function implementation
bool topupFunc(string selectedBank, double amount) {
    // Validate amount
    if (amount <= 0) {
        cout << "Invalid amount. Amount must be greater than 0." << endl;
        return false;
    }
    
    // Validate that user is logged in
    if (!loginSuccess) {
        cout << "User not logged in." << endl;
        return false;
    }
    
    // Validate bank selection
    if (selectedBank != "Bank A" && selectedBank != "Bank B") {
        cout << "Invalid bank selection." << endl;
        return false;
    }
    
    // Add amount to logged-in user's balance
    loginUser.balance += amount;
    
    // Update the balance in the allUsers vector
    for (int i = 0; i < allUsers.size(); i++) {
        if (allUsers[i].userid == loginUser.userid) {
            allUsers[i].balance = loginUser.balance;
            break;
        }
    }
    
    // Write updated data back to file
    ofstream outfile("../database/demo_user.txt");
    outfile << "id|userid|username|password|salt|balance" << endl;
    
    for (int i = 0; i < allUsers.size(); i++) {
        outfile << allUsers[i].id << "|" 
                << allUsers[i].userid << "|" 
                << allUsers[i].username << "|" 
                << allUsers[i].password << "|" 
                << allUsers[i].salt << "|" 
                << allUsers[i].balance << endl;
    }
    outfile.close();
    
    cout << "Top-up successful! Added " << amount << " from " << selectedBank 
         << ". New balance: " << loginUser.balance << endl;
    
    return true;
}

int main() {
    loadDataFromFile();
    registerFunc("newuser_auto", "pass123", 1000);
    login("newuser_auto", "pass123");
    if (!loginSuccess) {
        cout << "Login failed for newuser_auto" << endl;
        return 1;
    }

    cout << "Logged in: " << loginUser.username << " | Balance: " << loginUser.balance << " baht" << endl;
    if (!topupFunc("Bank A", 500)) {
        cout << "Topup failed" << endl;
        return 1;
    }

    cout << "After topup: " << loginUser.balance << " baht" << endl;


    return 0;
}