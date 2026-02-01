#pragma once

struct TransactionList{
    TransactionList *next=nullptr;
    double ammount=0.0;
    char type=' ';
};
struct SessionRecord{
    SessionRecord *next=nullptr;
    double ammount=0.0;
    int accnum=0;
};

struct User{// User Node
    int accnum=0;//account number
    int PIN=0;
    double balance=0.0;
    int maxtrans=5;//transactions limit
    TransactionList *List=nullptr;
};

