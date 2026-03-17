#include "Data.h"
#include "datahandler.h"
#include "UI.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>
using namespace std;

int LoadData(unordered_map<int, User> &accounts)
{
    ifstream ATMDATA("DATA/user.txt");
    if (!ATMDATA)
    {
        return 0;
    }
    string line;

    while (getline(ATMDATA, line))
    {
        stringstream data(line);
        string temp;
        User U;
        U.maxtrans = 5;

        getline(data, temp, '|');
        U.accnum = stoi(temp);

        getline(data, temp, '|');
        U.PIN = stoi(temp);

        getline(data, temp, '|');
        U.balance = stod(temp);
        accounts[U.accnum] = U;
    }
    return 1;
}

int SaveData(unordered_map<int, User> &accounts)
{
    ofstream ATMDATA("Data/user.dat", ios::out | ios::trunc);
    if (!ATMDATA)
        return 0;
    for (const auto &pair : accounts)
    {
        const User &u = pair.second;

        ATMDATA << u.accnum << "|" << u.PIN << "|" << u.balance << "\n";
    }
    ATMDATA.close();
    return 1;
}

int Record(SessionRecord *Record)
{
    ofstream record("Data/record.dat", ios::app);
    if (!record)
        return 0;
    record << endl;
    const int width = 60;
    const int col1 = 20;
    const int col2 = 36;
    string title = "Transaction Record";
    drawTitle(record,title);
    record << "|" << left <<setw(col1)<< "Account Number" << "|" <<right<<setw(col2)<< "Transaction Amount" << "|" << endl;
    
    while (Record != NULL)
    {   TransactionRecordRow(record,Record->accnum,Record->amount);
        drawDivider(record,60,'-');
        Record = Record->next;
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