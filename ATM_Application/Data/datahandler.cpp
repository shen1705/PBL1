#include "Data.h"
#include "datahandler.h"
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
    ofstream ATMDATA("DATA/user.txt", ios::out | ios::trunc);
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
    ofstream record("DATA/record.txt", ios::app);
    if (!record)
        return 0;
    record << endl;
    const int width = 60;
    const int col1_w = 20;
    const int col2_w = 36;
    string title = "Transaction Record";
    record << "+" << string(width - 2, '=') << "+" << endl;
    int padding = (width - 2 - title.length()) / 2;
    record << "|" << setw(padding + title.length()) << right << title
           << setw(width - 2 - padding - title.length() + 1) << "|" << endl;
    record << "+" << string(width - 2, '=') << "+" << endl;
    
    record << "|" << left <<setw(col1_w)<< "Account Number" << "|" <<right<<setw(col2_w)<< "Transaction Amount" << "|" << endl;
    
    
    while (Record != NULL)
    {   record << "|" << left << setw(col1_w) << (" " + to_string(Record->accnum)) 
               << "|" << right << setw(col2_w) << (to_string((int)Record->amount) + " ") 
               << "|" << endl;
        record << "|" << string(width - 2, '-') << "|" << endl;
        Record = Record->next;
    }
    record << "+" << string(width - 2, '=') << "+" << endl;
    record.close();
    return 1;
}
