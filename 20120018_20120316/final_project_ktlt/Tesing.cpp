//
// encoding: UTF-8 with BOM
// - So in order to print wide string to console output / read input from console we must use _setmode...
// - Use codecvt_utf8 for writing/reading from files
//
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_
#include <iostream>
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <string>
#include <locale>
#include <codecvt> //possible C++11?
#include <fstream>
using namespace std;
int wmain(int argc, wchar_t* argv[])
{
    _setmode(_fileno(stdout), _O_WTEXT); //needed for output
    _setmode(_fileno(stdin), _O_WTEXT); //needed for input
    // nhớ chuyển font của console sang Consolas (size 16)
    std::wstring username = L"Lâm\n\n";
    wchar_t gender = L'a';
    int age = 11;
    // lưu file tiếng Việt (UTF-8 without BOM)
    std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);  // UTF-8
    std::wofstream fout(L"Testing.inp");
    if (!fout) {
        std::wcout << L"Không thể tạo file userinfo-c++.txt\n";
    }
    else {
        fout.imbue(loc);
        fout << username << L"\n" << gender << L"\n" << age << L"\n";
        fout.close();
    }

    // đọc file tiếng Việt (định dạng UTF-8 without BOM)
    std::wifstream fin(L"Testing.inp");
    if (!fin) {
        std::wcout << L"Không thể đọc file userinfo-c++.txt\n";
    }
    else {
        fin.imbue(loc);
        std::getline(fin, username);
        fin >> gender >> age;

        std::wcout << L"Họ tên: " << username << L"\nGiới tính: "
            << (gender == L'a' ? L"Nam" : (gender == L'b' ? L"Nữ" : L"Không xác định"))
            << L"\nTuổi: " << age << L"\n\n";

        fin.close();
    }


    std::wcout << L"Chương trình kết thúc.\n";
}