#include "auth.h"
#include <string>
#include <iostream>
#include <limits>
using namespace std;




int ITauth() {
    const string system_password = "12345";
    string password = "";

    cout << "IT authentication required" << endl;
    cout << "Enter IT password: ";
    
    cin>>password;

    if (password == system_password) {
        cout << "Access Granted." << endl;
        return 1; 
    } else {
        cout << "Access Denied." << endl;
        return 0; 
    }
}



int Userauth(int pin){
    int PIN;
    cout << "Enter PIN: ";
    
    // Added safety check: if user types letters instead of numbers
    if (!(cin >> PIN)) {
        cin.clear(); // Clear error flag
        cin.ignore(1000, '\n'); // Discard bad input
        return 0;
    }
    
    cin.ignore(1000, '\n'); // Clear the newline left by cin >>
    return PIN == pin;
}