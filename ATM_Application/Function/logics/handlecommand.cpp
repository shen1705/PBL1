#include "handlecommand.h"
#include "auth.h"
#include "Data.h"
#include "UI.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void handlecommand(const string &cmd, int &running, unordered_map<int, User> &accounts, SessionRecord *&Record)
{

    if (cmd == "help")
        drawHelpBox();
    else if (cmd == "deposit" || cmd == "withdraw" || cmd == "balance" || cmd == "history")
    {
        int accountnumber;
        cout << "Please input your account number:";
        if (!(cin >> accountnumber))
        { // input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        if (accounts.count(accountnumber))
        {
            if (Userauth(accounts[accountnumber].PIN))
            {
                if (cmd == "deposit")
                    transaction(accounts[accountnumber], deposit, 'd', Record);
                else if (cmd == "withdraw")
                    transaction(accounts[accountnumber], withdraw, 'w', Record);
                else if (cmd == "balance")
                    ShowBalance(accounts[accountnumber]);
                else if (cmd == "history")
                    ShowHistory(accounts[accountnumber]);
            }
        }
        else
            cout << "Can not find your account" << endl;
    }
    else if (cmd == "shutdown")
    {
        if (ITauth())
            shutdown(running);
        else
            cout << "Authorization is failed" << std::endl;
    }
    else
        cout << "Unknown command. Type 'help'." << endl;
}

void shutdown(int &running)
{
    cout << "shutting down" << endl;
    running = 0;
}

void ShowBalance(User &U)
{
    cout << "Your balance:" << U.balance << endl;
}
void ShowHistory(User &U)
{
    int i = 1;
    TransactionList *current = U.List;
    if (current == nullptr)
    {
        cout << "No history was found." << endl;
        return;
    }
    while (current != NULL)
    {
        if (current->type != ' ')
            cout << i++ << ". Type: " << current->type << " Amount: " << current->ammount << endl;
        current = current->next;
    }
}
int withdraw(User &U, double ammount)
{
    if (U.balance > ammount)
    {
        U.balance -= ammount;
        cout << "withdraw successfully. Your new balance:" << U.balance << endl;
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
    cout << "deposit successfully. Your new balance:" << U.balance << endl;
    return 1;
}

void transaction(User &U, int (*type)(User &, double), const char transtype, SessionRecord *&Record)
{
    if (U.maxtrans != 0)
    {
        double ammount;
        cout << "Account:" << U.accnum << endl;
        cout << "Your current balance: " << U.balance << endl;
        cout << "------------------------------------" << endl;
        cout << "Enter ammount: ";
        if (!(cin >> ammount))
        { // input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        int success = type(U, ammount);

        if (success)
        {
            if (transtype == 'w')
                ammount = -ammount;

            TransUpdt(U, ammount, transtype);
            TransRecord(U, ammount, Record);
            U.maxtrans--;
            showMessageAndDelay();
            system("cls");
            drawMenuBox();
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
    newNode->next= U.List;
    U.List=newNode;
}

void TransRecord(User &U, double ammount, SessionRecord *Record)
{
    SessionRecord *newNode = new SessionRecord;
    newNode->accnum=U.accnum;
    newNode->ammount=ammount;
    newNode->next = Record;
    Record=newNode;
}

void Shutdown(int &running)
{
    if (ITauth())
    {
    }
    else
        cout << "Authorization is failed" << endl;
}