#include "handlecommand.h"
#include "auth.h"
#include "Data.h"

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;


void commandlist(){
    cout<<"========================================"<<endl;
    cout<<"  deposit   - Deposit money"<<endl
        <<"  withdraw  - Withdraw money"<<endl
        <<"  balance   - Show balance"<<endl
        <<"  history   - Show transactions"<<endl
        <<"  help      - Show this list"<<endl
        <<"  shutdown  - Shutdown ATM"<<endl;
    cout<<"========================================"<<endl;
}

void handlecommand(const string &cmd,int &running,unordered_map<int,User>& accounts){
   
    if(cmd == "help")
            commandlist();
    else if (cmd=="deposit"||cmd=="withdraw"||cmd=="balance"||cmd=="history"){
        int accountnumber;
        cout<<"Please input your account number:";
        if (!(cin >> accountnumber)){//input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();            
            cin.ignore(1000, '\n'); 
            return;              
        }
        if(accounts.count(accountnumber)){
            if(Userauth(accounts[accountnumber].PIN)){
                if (cmd == "deposit") transaction(accounts[accountnumber],deposit,'deposit');
                else if (cmd == "withdraw") transaction(accounts[accountnumber],withdraw,'withdraw');
                else if (cmd == "balance") ShowBalance(accounts[accountnumber]);
                else if (cmd == "history")ShowHistory(accounts[accountnumber]);
    
            }
        }
        else cout<<"Can not find your account"<<endl;
    }    
    else if (cmd == "shutdown"){
        if(ITauth())shutdown(running);
        else cout<<"Authorization is failed"<<std::endl;
    }
    else cout << "Unknown command. Type 'help'."<<endl;
}

void shutdown(int &running){
    cout<<"shutting down"<<endl;
    running = 0;
}

void ShowBalance(User& U){   
    cout<< "Your balance:"<<U.balance<<endl;
}
void ShowHistory(User& U){
    int i = 1;
    while(U.List->next !=NULL){
        cout<<i<<"."<<U.List->type<<U.List->ammount;
        i++;
        U.List= U.List->next;
    }

}
int withdraw(User& U,double ammount){
    if(U.balance>ammount){
        U.balance-=ammount;
        cout<<"withdraw successfully. Your new balance:"<<U.balance<<endl;
        return 1;
    }
    else{
        cout<<"Invalid.You dont have enough money to withdraw" <<endl;
        return 0;
    }
}

int deposit(User& U,double ammount){
    U.balance+=ammount;
    cout<<"deposit successfully. Your new balance:"<<U.balance<<endl;
    return 1;
}

void transaction(User& U,int (*type)(User&,double),const char transtype){
    if(U.maxtrans!=0){
        double ammount;
        cout<<"Account:"<<U.accnum<<endl;
        cout<<"Your current balance: "<< U.balance<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"Enter ammount: ";
        if (!(cin >> ammount)) {//input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();            
            cin.ignore(1000, '\n');
            return;                 
        }
        int success = type(U,ammount);
        
        if(success) {
            if (transtype == 'withdraw'){
                record(U,-ammount,'withdraw');
            } 
            else if(transtype == 'deposit'){
                record(U,ammount,'deposit');
            }
        U.maxtrans--;}
    }
    else cout<<"Transaction limit reached"<<endl;
}

void record(User& U, double ammount,char type){
while(U.List->next !=NULL){
    U.List=U.List->next;
}
    TransactionList* L = new TransactionList;
    U.List->next = L;
    L->ammount=ammount;
    L->type = type;
}

