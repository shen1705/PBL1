#pragma once
#include <string>


// basic
void commandlist();
void handlecommand(const std::string &cmd, int &running,unordered_map<int,User>& accounts);
void shutdown(int &running);

// Data 
int search();
void ShowBalance();
void ShowHistory();

// Transaction type
int withdraw(User U,double money,double balance[]);
int deposit(User U,double money,double balance[]);

// Transaction
void transaction(User U,int (*type)(User,double,double));

// Record
void record( );

