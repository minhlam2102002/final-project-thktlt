#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <utility>
#include "stringFunction.h"
#include "queryFunction.h"
#include "createMetadata.h"
using namespace std;

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
void goToXy(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;
    SetConsoleCursorPosition(hStdout, Position);
}

void drawRect(int x, int y, int a, int b) {
    goToXy(x, y);
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            if (i == 0 || (i == a - 1 && j != 0 && j != b - 1))
                cout << char(220);
            else if (j == 0 || j == b - 1) {
                cout << char(219);
            }
            else cout << ' ';
        }
        goToXy(x, y + i + 1);
    }
}
bool chkIn(char c, char s[32]) {
    for (int i = 0; i < 32; i++) {
        if (c == s[i]) {
            return true;
        }
    }
    return false;
}
char deli[] = { ',','.','-','\'','+','*','/','\"','!','@','#','$','%','^','&','(',')','=','_','[',']','{','}','\\','|',';',':','<','>','?','`','~' };
string input() {
    int n;
    char c;
    string query;
    while (true)
    {
        c = _getch();
        if (chkIn(c, deli) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '\b' || c == 32 || (c <= '9' && c >= '1') || (int)c == -32) {
            if ((int)c == -32) {
                char tmp = _getch();
                if (tmp == 72 || tmp == 75 || tmp == 77 || tmp == 80)
                    continue;
            }
            query += c;
        }
        if (c == '\r')
            break;
        else if (c == '\b')
        {
            if (query.size() != 1)
                query.pop_back();
            query.pop_back();
        }
        if (query.size() <= 35)
        {
            goToXy(22, 8); //search bar
            cout << "                                   ";
            goToXy(22, 8);
            cout << query;
        }
        else if (query.size() > 35)
        {
            goToXy(22, 8); //search bar
            cout << "                                   ";
            goToXy(22, 8);
            for (int i = query.size() - 35; i < query.size(); i++)
            {
                cout << query[i];
            }
        }
    }
    return query;
}

bool isValidChoice(const string& str)
{
    for (int i = 0;i<str.size();i++) {
        if (str[0] == '-')
            continue;
        if (isdigit(str[i]) == 0) return false;
    }
    return true;
}
void UI(Data& metadata) {
    string n; int choice;
    string file_name;
    SetColor(0, 14);
    do {

        cout << "Input \"*1\"~\"*5\": \n1. Search    |    2. Add file    |    3. Detele file    |    4. Choose folder    |    5. Exit";
        cout << "\n\n\n\n\n\t\t\t\t\tSEARCH ENGINE\n";
        drawRect(20, 7, 3, 55);
        goToXy(60, 8); cout << "| COMMAND: ";
        cin >> n;
        if (n == "*1") {
            goToXy(22, 8); //search bar
            string search = input();
            vector<pair<string, int>> res;
            Search(metadata, search, res);  //do query
            int page = res.size() / 5 + (res.size() % 5 != 0);
            for (int i = 0; i < page; i++) {
                for (int j = i * 5; j < res.size() - 5 * i; j++) {
                    goToXy(20, 10 + j); cout << res[j].first << ' ' << res[j].second;
                }
                goToXy(80, 7); cout << "Enter 1~5 to see detail.";
                goToXy(80, 8); cout << "Enter \"0\" to go to previous page.";
                goToXy(80, 9); cout << "Enter \"6\" to go to next page.";
                goToXy(80, 10); cout << "Enter \"-1\" to back to menu: ";
                goToXy(89, 20);
                cout << "Page " << i + 1;
                if (i == page - 1) {
                    goToXy(40, 22); cout << "This is the end of query.";
                }
                do {
                    goToXy(70, 8); cout << "   "; goToXy(70, 8); cin >> n;
                } while (!isValidChoice(n));
                choice = stoi(n);
                // check if input is valid
                // next demand
                if (choice == -1) {
                    break;
                }
                if (choice == 0) {
                    i -= 2;
                    goToXy(20, 22);
                    cout << "                             ";
                }
                if (choice == 6)
                    continue;
                if (choice != 0) {
                    system("cls");
                    cout << "\t\t\t***Enter any key to back.***";
                    cout << "\nday la detail ne\nDayla detail ne\nDay la detail ne ";
                    //go to page 2, see the detail
                    cout << "\nPress any key to back to menu"; _getch();
                    i--;
                    system("cls");
                    cout << "Input \"*1\"~\"*5\": \n1. Search    |    2. Add file    |    3. Detele file    |    4. Choose folder    |    5. Exit";
                    cout << "\n\n\n\n\n\t\t\t\t\tSEARCH ENGINE\n";
                    drawRect(20, 7, 3, 55);
                    goToXy(60, 8); cout << "| COMMAND: ";
                }
            }
        }
        if (n == "*2" || n == "*3") {
            goToXy(20, 10); cout << "Enter file name: ...";
            goToXy(22, 8); //search bar
            string path = input();
            if (n == "*2") {
                //add file
                goToXy(20, 10); cout << metadata.addFile(path);
                goToXy(20, 11); cout << "Press any key to back to menu"; _getch();
            }
            else {
                //delete file
                goToXy(20, 10); cout << metadata.deleteFile(path);
                goToXy(20, 11); cout << "Press any key to back to menu"; _getch();
            }
        }
        if (n == "*4") {
            goToXy(20, 10); cout << "Enter folder name: ...";
            goToXy(22, 8); //search bar
            string path = input();
            if (!checkFile(path)) {
                goToXy(20, 10); cout << "The folder is not exist ...";
            }
            else {
                goToXy(20, 10); cout << "Training data ...          ";
                createMetadata(path);
                goToXy(20, 10); cout << "Completed. Press any key to back to menu. "; _getch();
            }
        }
        if (n == "*5")
            return;
        system("cls");
    } while (true);
}