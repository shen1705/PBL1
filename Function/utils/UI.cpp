#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <thread> 
#include <chrono> 
#include <cstdlib>
#include <vector>
#include <sstream>
#include "UI.h"

using namespace std;

static const int FRAME_WIDTH = 100;
static const int LOGIN_FRAME_WIDTH = 100;


static void drawFrameTop(ostream &os)
{
    os << "+" << string(FRAME_WIDTH - 2, '=') << "+" << endl;
}

static void drawFrameBottom(ostream &os)
{
    os << "+" << string(FRAME_WIDTH - 2, '=') << "+" << endl;
}

static void drawFrameTextLine(ostream &os, const string &text)
{
    os << "| " << left << setw(FRAME_WIDTH - 4) << text << " |" << endl;
}

static void drawFrameCenteredLine(ostream &os, const string &text)
{
    int innerWidth = FRAME_WIDTH - 4;
    int leftPadding = 0;
    if (static_cast<int>(text.length()) < innerWidth)
    {
        leftPadding = (innerWidth - static_cast<int>(text.length())) / 2;
    }
    os << "| " << string(leftPadding, ' ') << text
       << string(innerWidth - leftPadding - text.length(), ' ') << " |" << endl;
}

// utils
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    cout << "Nhan Enter de quay lai...";
    if (!cin.good())
    {
        cin.clear();
    }
    string line;
    getline(cin, line);
}

void delay(int seconds)
{
    this_thread::sleep_for(chrono::seconds(seconds));
}

void drawTitle(ostream &os, string title)
{
    drawFrameTop(os);
    drawFrameCenteredLine(os, title);
}

void drawDivider(ostream &os, int width, char symbol)
{
    os << "|" << string(width - 2, symbol) << "|" << endl;
}

void History(ostream &os, int no, double amount, string type)
{
    const int col1 = 10;
    const int col2 = 30;
    const int col3 = 56;

    ostringstream amountStream;
    amountStream << fixed << setprecision(2) << amount;
    string amtStr = amountStream.str();

    os << "|" << left << setw(col1) << (" " + to_string(no))
       << "|" << left << setw(col2) << (" " + type)
       << "|" << right << setw(col3) << amtStr << "|" << endl;
}

void TransactionRecordRow(ostream &os, int accnum, string typeStr, double amount)
{
    os << "|" << left << setw(30) << (" " + to_string(accnum))
       << "|" << left << setw(24) << (" " + typeStr)
       << "|" << right << setw(42) << fixed << setprecision(2) << amount << "|" << endl;
}

// Main UI 
void drawLoginFieldLine(const string &label, const string &value)
{
    const int innerWidth = LOGIN_FRAME_WIDTH - 4;
    string line = label + value;
    if (static_cast<int>(line.size()) > innerWidth)
    {
        line = line.substr(0, innerWidth);
    }
    cout << "| " << left << setw(innerWidth) << line << " |" << endl;
}

void drawCredentialBox(const string &accNumValue, const string &pinValue, const string &note)
{
    clearScreen();
    cout << "+" << string(LOGIN_FRAME_WIDTH - 2, '=') << "+" << endl;
    cout << "| " << left << setw(LOGIN_FRAME_WIDTH - 4) << "WELCOME TO ATM" << " |" << endl;
    cout << "|" << string(LOGIN_FRAME_WIDTH - 2, '-') << "|" << endl;
    if (!note.empty())
    {
        drawLoginFieldLine("Thong bao: ", note);
    }
    else
    {
        drawLoginFieldLine("Thong bao: ", "Vui long nhap thong tin dang nhap.");
    }
    cout << "|" << string(LOGIN_FRAME_WIDTH - 2, '-') << "|" << endl;
    drawLoginFieldLine("Acc Num  : ", accNumValue);
    drawLoginFieldLine("Enter PIN: ", pinValue);
    cout << "+" << string(LOGIN_FRAME_WIDTH - 2, '=') << "+" << endl;
}

void drawProjectIntro()
{
    clearScreen();
    drawFrameTop(cout);
    drawFrameCenteredLine(cout, "DU AN CO SO LAP TRINH");
    drawDivider(cout, FRAME_WIDTH, '-');
    drawFrameCenteredLine(cout, "DE TAI 701: XAY DUNG UNG DUNG THUC HIEN GIAO DICH TREN MAY ATM");
    drawFrameTextLine(cout, "");
    drawFrameCenteredLine(cout, "GIANG VIEN HUONG DAN: TRAN HO THUY TIEN");
    drawFrameTextLine(cout, "");
    drawFrameCenteredLine(cout, "SINH VIEN THUC HIEN: NGUYEN XUAN AN");
    drawFrameCenteredLine(cout, "NGUYEN HOANG MINH");
    drawFrameTextLine(cout, "");
    drawFrameCenteredLine(cout,"KHOA: FAST");
    drawFrameCenteredLine(cout,"LOP: 23PFIEV3");
    drawFrameBottom(cout);
    cout << endl;
}

void drawUserBox(int accnum, double balance, int maxtrans)
{
    clearScreen();
    drawTitle(cout, "ACCOUNT NUMBER: " + to_string(accnum));
    drawDivider(cout, FRAME_WIDTH, '-');

    string balStr = "So du hien tai: " + to_string(balance);
    string limStr = "So lan giao dich con lai: " + to_string(maxtrans);
    drawFrameTextLine(cout, balStr);
    drawFrameTextLine(cout, limStr);
    drawDivider(cout, FRAME_WIDTH, '-');

    drawFrameTextLine(cout, "1. Deposit money - Gui tien");
    drawFrameTextLine(cout, "2. Withdraw money - Rut tien");
    drawFrameTextLine(cout, "3. Show transactions - Lich su giao dich");
    drawFrameTextLine(cout, "4. Log out - Dang xuat");
    drawFrameBottom(cout);
}

void showMessageAndDelay()
{
    cout << "Processing transaction..." << endl;
    delay(2);
}

void logoutannounce()
{
    cout << "Logging out..." << endl;
    delay(2);
}

void loginfailedannounce()
{
    cout << "Login Failed! Wrong PIN" << endl;
    delay(2);
}

void shutdownAnnounce()
{
    clearScreen();
    cout << "Saving DATA..." << endl;
    delay(2);
    for (int i = 3; i > 0; i--)
    {
        clearScreen();
        cout << "Shutting down in " << i << endl;
        delay(1);
    }
}

void systemMenu()
{
    clearScreen();
    drawTitle(cout, "IT ADMIN MENU");
    drawDivider(cout, FRAME_WIDTH, '-');
    drawFrameTextLine(cout, "1. Start ATM Session (Launch UI)");
    drawFrameTextLine(cout, "0. Shutdown Entire Hardware");
    drawFrameBottom(cout);
}