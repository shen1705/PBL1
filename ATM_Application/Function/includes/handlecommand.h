#pragma once
#include <string>

enum TransactionType
{
    withdraw,
    deposit
};
// basic
void handlecommand(const std::string &cmd, int &running,User &current,int &user_status, SessionRecord *&Record);

// Data
void ShowHistory(User &U);

// Transaction type
int withdraw(User U, double money);
int deposit(User U, double money);

// Transaction
void transaction(User U, int (*type)(User, double, double), char transtype);

// Record
void TransUpdt(User &U, double ammount, char type);
void TransRecord(User &U, double ammount,SessionRecord *&Record);