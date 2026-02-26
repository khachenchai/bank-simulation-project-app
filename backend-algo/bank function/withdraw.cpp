#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<random>
#include<ctime>
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
User loginUser;
bool loginSuccess = false;
int counter = 0;

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

void saveUserToFile() {
    ofstream file("../database/demo_user.txt");
    file << "id|userid|username|password|salt|balance" << endl;
    for (int i = 0; i < allUsers.size(); i++) {
        file << allUsers[i].id << '|' << allUsers[i].userid << '|' << allUsers[i].username << '|'
             << allUsers[i].password << '|' << allUsers[i].salt << '|' << allUsers[i].balance << endl;
    }
    file.close();
}

string generateOTP() {
    srand(time(0) + rand());
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);
    
    string otp = "";
    for (int i = 0; i < 6; i++) {
        otp += to_string(dis(gen));
    }
    return otp;
}

string withdrawFunc(double amount) {
    if (amount > loginUser.balance) {
        return "";
    }
    string otp = generateOTP();
    loginUser.balance -= amount;
    for (int i = 0; i < allUsers.size(); i++) {
        if (allUsers[i].username == loginUser.username) {
            allUsers[i].balance = loginUser.balance;
            break;
        }
    }

    saveUserToFile();
    return otp;
}


int main() {
    
    loadDataFromFile();
    registerFunc("testuser", "password123", 5000);
    login("testuser", "password123");
    withdrawFunc(2000);
    
    return 0;
}
