#pragma once

struct TransactionList
{
    TransactionList *next=nullptr;
    double amount=0.0;
    char type=' ';
};

struct SessionRecord
{
    SessionRecord *next=nullptr;
    double amount=0.0;
    int accnum=0;
    char type;
};

struct User //Người dùng
{
    int accnum=-1;//account number
    int PIN=0;//PIN
    double balance=0.0;//account balance
    int maxtrans=5;// max transitions
    TransactionList *List;// transactions history
};

struct UserList 
{
    User data;
    UserList *next;
};