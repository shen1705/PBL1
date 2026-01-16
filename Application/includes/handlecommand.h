#pragma once



// basic
void commandlist();
void handlecommand(const std::string &cmd, int &running, int accnum[], int PIN[], double balance[], int count, int current[], int history[], double ammount[]);
void shutdown(int &running);

// Data 
int search(int id, int accnum[], int count, int &index);
void ShowBalance(int index, double balance[]);
void ShowHistory(int index, int history[], double ammount[], int accnum[]);

// Transaction type
int withdraw(int index, double money, double balance[]);
int deposit(int index, double money, double balance[]);

// Transaction
void transaction(int index, double balance[], int current[], int history[], double ammount[], int (*type)(int, double, double*), int accnum[]);

// Record
void record(int index, int history[], double ammount[], int accnum[], double money);

