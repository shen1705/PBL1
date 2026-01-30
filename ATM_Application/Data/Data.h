#pragma once

struct TransactionList{
    TransactionList *next;
    double ammount;
    char type;
};
struct SessionRecord{
    SessionRecord *next;
    double ammount;
    int accnum;
};

struct User{// User Node
    int accnum;//account number
    int PIN;
    double balance;
    int maxtrans;//transactions limit
    TransactionList *List;
};

