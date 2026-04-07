#pragma once
#include <string>
#include "Data.h"


void handlecommand(const std::string &cmd,User &current,int &user_status, SessionRecord *&Record);

// Data
void ShowHistory(User &U);

// Transaction type
int withdraw(User &U, double money);
int deposit(User &U, double money);

// Transaction
void transaction(User &U, int (*type)(User&, double), char transtype,SessionRecord *&Record);

// Record
void TransUpdt(User &U, double amount, char type);
void TransRecord(User &U, double amount,SessionRecord *&Record,char type);
