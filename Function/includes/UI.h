#pragma once
#include <iostream>
#include <string>
#include "Data.h"
using namespace std;
//utils
void clearScreen();
void delay(int seconds);
void pauseScreen();
void drawTitle(std::ostream &os, std::string title);
void drawDivider(std::ostream &os, int width, char symbol);
// Records
void History(std::ostream &os, int no, double amount, std::string type);
void TransactionRecordRow(ostream &os, int accnum, string typeStr, double amount);
// Main 
void drawLoginFieldLine(const string &label, const string &value);
void drawCredentialBox(const string &accNumValue, const string &pinValue, const string &note);
void drawUserBox(int accnum, double balance, int maxtrans);
void drawManagerBox();
void showMessageAndDelay();
void logoutannounce();      
void loginfailedannounce(); 
void shutdownAnnounce();    
void drawProjectIntro();