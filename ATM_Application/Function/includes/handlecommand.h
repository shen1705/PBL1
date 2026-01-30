#pragma once
#include <string>
#include <unordered_map>
#include "Data.h"

// basic
void handlecommand(const std::string &cmd, int &running, std::unordered_map<int, User> &accounts, SessionRecord *&Record);


// Data
int search();
void ShowBalance(User &U);
void ShowHistory(User &U);

// Transaction type
int withdraw(User &U, double money);
int deposit(User &U, double money);

// Transaction
void transaction(User &U, int (*type)(User&, double), char transtype,SessionRecord *&Record);

// Record
void TransUpdt(User &U, double ammount, char type);
void TransRecord(User &U, double ammount,SessionRecord *Record);

//shutdown
void shutdown(int& running);