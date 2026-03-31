#pragma once
#include <iostream>
#include <string>
#include "Data.h"
using namespace std;
//utils
void clearScreen();
void pauseScreen();
void drawTitle(std::ostream &os, std::string title);
void drawDivider(std::ostream &os, int width, char symbol);
// Records
void History(std::ostream &os, int no, double amount, std::string type);
void TransactionRecordRow(ostream &os, int accnum, string typeStr, double amount);
// Main 
void systemMenu();
void drawMenuBox();
void drawUserBox(int accnum, double balance, int maxtrans);
void showMessageAndDelay();
void logoutannounce();      
void loginfailedannounce(); 
void shutdownAnnounce();    
void delay(int seconds);