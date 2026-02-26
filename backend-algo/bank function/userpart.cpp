#include"userpart.h"
#include<fstream>
#include<random>
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

int main() {
    User systemRun;
    User::Bank transaction;
    systemRun.loadDataFromFile();
    systemRun.login("chenchoy","kontairakjing");
    systemRun.reloadLoginUser();
    systemRun.rewritetxt();
    systemRun.login("dog","sleepy");
    transaction.topupFunc("Bank A", 500);
    systemRun.registerFunc("gg","password123",500);
    systemRun.login("gg","password123");
    return 0;
}