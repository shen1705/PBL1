#pragma once
#include <string>

enum TransactionType{
    withdraw,
    deposit
};
// basic
void commandlist();
void handlecommand(const std::string &cmd, int &running,unordered_map<int,User>& accounts);
void shutdown(int &running);

// Data 
int search();
void ShowBalance(User &U);
void ShowHistory(User& U);

// Transaction type
int withdraw(User U,double money);
int deposit(User U,double money);

// Transaction
void transaction(User U,int (*type)(User,double,double),char transtype);

// Record
void record(User& U, double ammount,char type);



