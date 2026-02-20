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
using namespace std;
struct User {
    int id;
    string userid;
    string username;
    string password;
    string salt;
    double balance;
};
vector<User> allUsers;
string hashPassword(const string& password, const string& salt) {
    hash<string> hasher;
    size_t hashed = hasher(password + salt);
    return to_string(hashed);
}
string generateSalt(int len = 16) {
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
void loadDataFromFile(){
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
void registerFunc(string username,string password, double balance){
    loadDataFromFile();
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
void login(string inputusername,string inputpassword){
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
void reloadLoginUser(){
    for(int i=0;i<allUsers.size();i++){
        if(allUsers[i].userid == loginUser.userid){
            allUsers[i] = loginUser;
            break;
        }
    }
}
void rewritetxt(){
    ofstream outFile("../database/demo_user.txt");
    if (outFile.is_open()) {
        outFile << "id|userid|username|password|salt|balance" << endl;
        for (const auto& user : allUsers) {
            outFile << user.id << '|' << user.userid << '|' << user.username << '|' << user.password << '|' << user.salt << '|'<< user.balance << endl;
        }
        outFile.close();
}
}

string getDateTimeStr() {
        auto now = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(now);

        tm tm{};
    #ifdef _WIN32
        localtime_s(&tm, &t);   // Windows
    #else
        localtime_r(&t, &tm);   // Linux / macOS
    #endif

        ostringstream oss;
        oss << put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
}

void transfer(string inputuserid, double amount){
    loadDataFromFile();
    bool check = false, isAffort = true;
    for (int i=0;i<allUsers.size();i++){
        if(allUsers[i].userid == inputuserid){
            check = true;
            if(loginUser.balance < amount){
                // cout << "Not enough money\n"
                isAffort = false;
                break;
            }
            else{
                allUsers[i].balance += amount;
                loginUser.balance -= amount;
                reloadLoginUser();
                rewritetxt();
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

        transactionFileOut << id << '|' << dt << '|' << "transfer" << '|' << loginUser.userid << '|' << inputuserid << endl;

        transactionFileOut.close();
    }
}



int main() {
    loadDataFromFile();
    registerFunc("eq", "littlebear",0);
    registerFunc("chenchoy", "kontairakjing",1000);
    registerFunc("dog","sleepy",200);
    registerFunc("eq", "fahrakphor",500);//same username case test
    cout << "ID " << allUsers[0].id<<" UserID: " << allUsers[0].userid << " Username: " << allUsers[0].username << " Password: " << allUsers[0].password << " Salt: " << allUsers[0].salt << " Balance: " << allUsers[0].balance << endl;
    login("chenchoy","kontairakjing");
    cout << "ID " << loginUser.id<<" UserID: " << loginUser.userid << " Username: " << loginUser.username << " Balance: " << loginUser.balance << endl;
    transfer("123",2000);// wrong userid
    transfer("100041",200);
    cout << "ID " << allUsers[0].id<<" UserID: " << allUsers[0].userid << " Username: " << allUsers[0].username << " Password: " << allUsers[0].password << " Salt: " << allUsers[0].salt << " Balance: " << allUsers[0].balance << endl;
    cout << "ID " << loginUser.id<<" UserID: " << loginUser.userid << " Username: " << loginUser.username << " Balance: " << loginUser.balance << endl;
    return 0;
}