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

struct User 
{
    int accnum=-1;
    int PIN=0;
    double balance=0.0;
    int maxtrans=5;
    TransactionList *List;
};

struct UserList 
{
    User data;
    UserList *next;
};