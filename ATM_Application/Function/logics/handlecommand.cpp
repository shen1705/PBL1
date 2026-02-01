#include "handlecommand.h"
#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <iostream>
#include <string>
#include <limits>
#include <unordered_map>

using namespace std;

void handlecommand(const string &cmd, int &running, User &current,int &user_status, SessionRecord *&Record)
{

    if (cmd == "deposit")
        transaction(current, deposit, 'd', Record);
    else if (cmd == "withdraw")
        transaction(current, withdraw, 'w', Record);
    else if (cmd == "history")
        ShowHistory(current);
    else if (cmd=="exit"||cmd=="logout"){
        user_status =0;
    }
    else if (cmd == "shutdown")
    {
        if (ITauth())
            shutdown(running);
        else
            cout << "Authorization is failed" << std::endl;
    }
    else
        cout << "Unknown command." << endl;
}

void shutdown(int &running)
{
    running = 0;
}

void ShowHistory(User &U)
{
    int i = 1;
    while (U.List->next != NULL)
    {
        cout << i << "." << U.List->type << U.List->ammount;
        i++;
        U.List = U.List->next;
    }
}
int withdraw(User &U, double ammount)
{
    if (U.balance >= ammount)
    {
        U.balance -= ammount;
        cout << "withdraw successfully. " << U.balance << endl;
        return 1;
    }
    else
    {
        cout << "Invalid.You dont have enough money to withdraw" << endl;
        return 0;
    }
}

int deposit(User &U, double ammount)
{
    U.balance += ammount;
    cout << "deposit successfully. " << U.balance << endl;
    return 1;
}

void transaction(User &U, int (*type)(User &, double), const char transtype, SessionRecord *&Record)
{
    if (U.maxtrans != 0)
    {
        double ammount;
        cout << "Enter ammount: ";
        if (!(cin >> ammount))
        { // input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');;
            return;
        }
        int success = type(U, ammount);

        if (success)
        {   
            if (transtype == 'withdraw')
            {
                ammount = -ammount;
                TransUpdt(U, ammount, 'withdraw');
            }
            else if (transtype == 'deposit')
            {
                TransUpdt(U, ammount, 'deposit');
            }
            TransRecord(U, ammount, Record);
            U.maxtrans--;
            cout<<"Processing transaction";
            delay(2);
            system("cls");
            drawUserBox(U.accnum,U.balance,U.maxtrans);
        }
    }
    else
        cout << "Transaction limit reached" << endl;
    
}

void TransUpdt(User &U, double ammount, char type)
{
    TransactionList *newNode = new TransactionList;
    newNode->ammount = ammount;
    newNode->type = type;
    newNode->next = U.List;
    U.List = newNode;
}

void TransRecord(User &U, double ammount, SessionRecord *&Record)
{
    SessionRecord *newNode = new SessionRecord;
    newNode->accnum = U.accnum;
    newNode->ammount = ammount;
    newNode->next = Record;
    Record = newNode;
}
