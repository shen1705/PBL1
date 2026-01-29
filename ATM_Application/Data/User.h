#pragma once

struct User{// User Node
    int accnum;//account number
    int PIN;
    double balance;
    int maxtrans;//transactions limit

};

struct TransactionList{
    TransactionList *next;
    double ammount;
    int accnum;
};