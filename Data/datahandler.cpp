#include "Data.h"
#include "datahandler.h"
#include "UI.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

int LoadData(UserList* &accounts)
{
    ifstream ATMDATA("Data/user.dat");
    if (!ATMDATA) return 0;

    string line;
    UserList* current = nullptr;
    accounts = nullptr;

    while (getline(ATMDATA, line))
    {
        if (line.empty()) continue;
        stringstream data(line);
        string temp;
        User U;
        U.maxtrans = 10;

        getline(data, temp, '|');
        U.accnum = stoi(temp);

        getline(data, temp, '|');
        U.PIN = stoi(temp);

        getline(data, temp, '|');
        U.balance = stod(temp);
        U.List = nullptr;

        UserList* newNode = new UserList;
        newNode->data = U;
        newNode->next = nullptr;

        if (accounts == nullptr) {
            accounts = newNode;
            current = accounts;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }
    ATMDATA.close();
    return 1;
}

int SaveData(UserList* accounts)
{
    ofstream ATMDATA("Data/user.dat", ios::out | ios::trunc);
    if (!ATMDATA) return 0;
    
    UserList* current = accounts;
    while (current != nullptr)
    {
        const User &u = current->data;
        ATMDATA << u.accnum << "|" << u.PIN << "|" << u.balance << "\n";
        current = current->next;
    }
    ATMDATA.close();
    return 1;
}

int Record(SessionRecord *RecordNode) 
{   
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream filename;
    filename << "Data/record_" 
             << 1900 + ltm->tm_year << "-"
             << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
             << setfill('0') << setw(2) << ltm->tm_mday << "_"
             << setfill('0') << setw(2) << ltm->tm_hour << "-"
             << setfill('0') << setw(2) << ltm->tm_min << "-"
             << setfill('0') << setw(2) << ltm->tm_sec << ".dat";
    ofstream record(filename.str(), ios::out);
    if (!record) return 0;
    
    record << endl;
    
    record << "Session Time: " 
           << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " "
           << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << endl << endl;
        const int width = 100;
        const int col1 = 30;
        const int col2 = 24;
        const int col3 = 42;
    string title = "Transaction Record";
    
    drawTitle(record, title);
    

    record << "|" << left << setw(col1) << "Account Number" 
           << "|" << left << setw(col2) << "Type"
           << "|" << right << setw(col3) << "Transaction Amount" << "|" << endl;
    
    while (RecordNode != nullptr)
    {   
        string typeStr = (RecordNode->type == 'd') ? "Deposit" : "Withdraw";
        
        TransactionRecordRow(record, RecordNode->accnum, typeStr, RecordNode->amount);
        
        drawDivider(record, width, '-');
        RecordNode = RecordNode->next;
    }
    
    record << "+" << string(width - 2, '=') << "+" << endl;
    record.close();
    return 1;
}

void FreeHistory(User &U)
{
    TransactionList *current = U.List;
    while (current != nullptr)
    {
        TransactionList *temp = current;
        current = current->next;
        delete temp;
    }
    U.List = nullptr;
}