#include "auth.h"
#include <string>
#include <iostream>
#include <conio.h>
using namespace std;





int ITauth(){
    const string system_password = "12345";
    string password="";
    cout<<"IT authentication require"<<endl;
    char ch;
    cout<< "Enter IT password:";
    //ASCII required 

    //improved the input for user
    while((ch=_getch())!=13){//13 for ENTER
        if(ch==8){//backspace
            if(password.length()>0){//prevent error 
                password.pop_back();//delete from password 
                cout<<"\b \b";//delete the "*" from console(to hide password)
            }

        }
        else {
            password+=ch;//add char to password 
            cout<<"*";//print "*" to console (to hide password)
        }
    }
    cout<<endl;
    return password == system_password;//verification 
    
}


int Userauth(int pin){
    int PIN;
    cout<< "Enter PIN:";
    cin>>PIN;
    cin.ignore(1000, '\n');
    return PIN==pin;

}