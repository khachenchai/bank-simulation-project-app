#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include <ctime>
#include <chrono>
#include <format>
#include <iomanip>
#include"userpart.h"
using namespace std;

class Usertransaction {
    int id;
    string datetime;
    string transaction;
};

string hashPassword(const string& password, const string& salt) {
    hash<string> hasher;
    size_t hashed = hasher(password + salt);
    return to_string(hashed);
}
string generateSalt(int len) {
    const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, sizeof(charset) - 2);
        string salt;
        for (int i = 0; i < len; i++) {
            salt += charset[dis(gen)];
        }
        return salt;
}
vector<string> splitData(string rowData, char seperator) {
    string dataToAppend;
    vector<string> result;
    int count = 0;
    for (int i = 0; i < rowData.size(); i++) {
        if (rowData[i] == seperator) {
            result.push_back(dataToAppend);
            dataToAppend = "";
        } else dataToAppend += rowData[i];
    }
    result.push_back(dataToAppend);
    return result;
}
int counter = 0;
void User::loadDataFromFile(){
    counter = 0;
    allUsers.clear();
    ifstream readfile("../database/demo_user.txt");
    string line;
    bool skipHeader = true;
    while (getline(readfile,line)){
        counter++;
        if (line == "" || line == "\r"){
            continue;
        }
        if (skipHeader) { skipHeader = false; continue; }
        vector<string> data = splitData(line,'|');
        User u;
        u.id = stoi(data[0]);
        u.userid = data[1];
        u.username = data[2];
        u.password = data[3];
        u.salt = data[4];
        u.balance = stod(data[5]);
        allUsers.push_back(u);
    }
}
void User::registerFunc(string username,string password, double balance){
    bool skipHeader = true;
    User u;
    u.username=username;
    u.password=password;
    u.userid = to_string(rand() % 900000 + 100000);
    for (int i = 0; i < allUsers.size(); i++) {
        if (allUsers[i].username == username) {
            cout << "Username already exists!" << endl;
            return;
        }
    }
    for(int i=0;i<allUsers.size();i++){
        if(allUsers[i].userid == u.userid){
        u.userid = to_string(rand() % 900000 + 100000);
        }
        else continue;
    }
    u.id = counter;
    string salt = generateSalt();
    string hash = hashPassword(password, salt);
    u.salt = salt;
    u.balance = balance;
    allUsers.push_back(u);
    ofstream user;
    user.open("../database/demo_user.txt",ios::app);
    user << u.id<<'|'<< u.userid <<'|'<<u.username<<'|'<<hash<<'|'<<u.salt<<'|'<<u.balance<<endl;
    user.close();
}

bool loginSuccess = false;
User loginUser;
void User::login(string inputusername,string inputpassword){
    loadDataFromFile();
    for (int i=0;i<allUsers.size();i++){
        if(allUsers[i].username == inputusername){
            string hashPass = hashPassword(inputpassword,allUsers[i].salt);
            if(hashPass == allUsers[i].password){
                cout << "Login susscess\n";
                loginSuccess = true;
                loginUser = allUsers[i];
                break;
            }
            else{
                cout << "Wrong password\n";
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
    ofstream outFile("../database/demo_user.txt");
    if (outFile.is_open()) {
        outFile << "id|userid|username|password|salt|balance" << endl;
        for (const auto& user : allUsers) {
            outFile << user.id << '|' << user.userid << '|' << user.username << '|' << user.password << '|' << user.salt << '|'<< user.balance << endl;
        }
        outFile.close();
}
}
bool User::Bank::topupFunc(string selectedBank, double amount) {
    if (amount <= 0) {
        cout << "Invalid amount. Amount must be greater than 0." << endl;
        return false;
    }
    if (selectedBank != "Bank A" && selectedBank != "Bank B") {
        cout << "Invalid bank selection." << endl;
        return false;
    }
    loginUser.balance += amount;
    User temp;
    temp.reloadLoginUser();
    temp.rewritetxt();
    return true;
}

string getDateTimeStr() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);

    tm local_tm{};
    localtime_s(&local_tm, &now_c);

    stringstream ss;
    ss << put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
   

void User::Bank::transfer(string inputuserid, double amount){

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

// vector<string> getUserTransaction(string filename, User loginuser){
//     vector<string> resulttransaction;
//     string line;
//     bool skipHeader = true;

//     ifstream infile(filename);

//     while (getline(infile,line){
        
//         vector<string> data = splitData(line,'|')

//         if (line == "" || line == "\r"){
//             continue;
//         }
//         if (skipHeader) { skipHeader = false; continue; }
//         vector<string> data = splitData(line,'|');
//         User u;


//     }
    
 

    
// }



int main() {

    User systemRun;
    User::Bank transaction;
    systemRun.loadDataFromFile();
    systemRun.registerFunc("gg","password123",500);
    systemRun.login("gg","password123");
    systemRun.registerFunc("dogshit","p4545435",5660);
    transaction.transfer("118467",500);
    return 0;
}