#include "handlecommand.h"
#include "auth.h"
#include "User.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;


void commandlist(){
    cout<<"========================================"<<endl;
    cout<<  "  deposit   - Deposit money"<<endl
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
                if (cmd == "deposit") transaction(deposit,);
                else if (cmd == "withdraw") transaction(,withdraw,);
                else if (cmd == "balance") ShowBalance();
                else if (cmd == "history")ShowHistory();
    
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

int search(int id,int accnum[],int count,int &index){
    for(int i=0; i<count;i++){
        if(id==accnum[i]){
            index=i;
            return 1;
        }
    }
    return 0;
}

void ShowBalance(int index,double balance[]){   
    cout<< "Your balance:"<<balance[index]<<endl;
}

int withdraw(User U,double money,double balance[]){
    if(balance[index]>money){
        balance[index]-=money;
        cout<<"withdraw successfully. Your new balance:"<<balance[index]<<endl;
        return 1;
    }
    else{
        cout<<"Invalid.You dont have enough money to withdraw" <<endl;
        return 0;
    }
}

int deposit(User U,double money,double balance[]){
    balance[index]+=money;
    cout<<"deposit successfully. Your new balance:"<<balance[index]<<endl;
    return 1;
}

void transaction(User U,int (*type)(int,double,double*)){
    if(U.maxtrans!=0){
        double money;
        cout<<"Account:"<<U.accnum<<endl;
        cout<<"Your current balance: "<< U.balance<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"Enter ammount: ";
        if (!(cin >> money)) {//input bug type error
            cout << "Invalid input! Please enter a number." << endl;
            cin.clear();            
            cin.ignore(1000, '\n');
            return;                 
        }
        int success = type(User U,double money,double balance[]);
        
        if(success) {
            if (type == withdraw){
                record(index, history, ammount, accnum, -money);
            } 
            else{
                record(index, history, ammount, accnum, money);
            }
        maxtrans[index]--;}
    }
    else cout<<"Transaction limit reached"<<endl;
}

void record(TransactionList){
    int i =0;
    while(history[i]!=0){
        i++;
    }
    history[i]=accnum[index];
    ammount[i]=money;
}

void ShowHistory(int index, int history[], double ammount[],int accnum[]){
    int i =0;
    int j =0;
    cout<<"Your transaction history:"<<endl;
    while( history[i]!=0){
        if(history[i]==accnum[index]){
            cout<<++j<<"." <<ammount[i]<<endl;
            i++;
        }
    }
}