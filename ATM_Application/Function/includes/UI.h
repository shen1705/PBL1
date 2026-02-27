#pragma once
#include <iostream>
#include <string>
#include "Data.h"

//utils
void clearScreen();
void pauseScreen();
void drawTitle(std::string title);
void drawDivider(int width, char symbol);
// Records
void History(int no, double amount, std::string type);
void TransactionRecordRow(int accNum, double amount);

// Main 
void drawMenuBox();
void drawUserBox(int accnum, double balance, int maxtrans);
void showMessageAndDelay();
void logoutannounce();      
void loginfailedannounce(); 
void shutdownAnnounce();    
void delay(int seconds);