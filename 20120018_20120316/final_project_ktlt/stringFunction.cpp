#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS

#include <fstream> 
#include <fcntl.h> //_O_WTEXT
#include <io.h>    //_setmode()
#include <locale>
#include <codecvt> 
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <regex>
#include "stringFunction.h"
#include "InOut.h"
//#include "InOut.h"
using namespace std;

void lowerCase(string& str) {
	for (int i = 0; i < str.size(); i++) {
		str[i] = tolower(str[i]);
	}
}
void fixWord(string& str) {
	for (int i = 0; i < str.size(); i++) {
		if (!((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9'))) {
			str[i] = ' ';
		}
	}
	for (int i = 0; i < str.size() - 1; i++) {
		if (str[i] == ' ' && str[i + 1] == ' ') {
			str.erase(i, 1);
			i--;
		}
	}
}
void extractWord(string content, vector<string>& words) {
	stringstream ss(content);
	string word;
	while (ss >> word) {
		words.push_back(word);
	}
}
void Z_algo(string& mom, string child) { // delete chil in string mom 
	string s = child + '*' + mom;
	int child_sz = child.size();
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (z[i - l] < r - i + 1) z[i] = z[i - l];
		else {
			r = max(r, i);
			while (s[r - i] == s[r]) r += 1;
			z[i] = r - i;
			r -= 1;
			l = i;
		}
	}
	for (int i = child_sz; i < n; i++) {
		if (z[i] == child_sz) {
			mom.erase(i - child_sz - 1, child_sz + 1);
		}
	}
}
void deleteStopWord(string& content, vector<string> stopWords) {
	for (string sWord : stopWords) {
		Z_algo(content, sWord);
	}
}

void XoaDau(string &txt, std::wstring w_txt) {
	w_txt = std::regex_replace(w_txt, std::wregex(L"à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ|/g"), L"a");
	w_txt = std::regex_replace(w_txt, std::wregex(L"À|Á|Ạ|Ả|Ã|Â|Ầ|Ấ|Ậ|Ẩ|Ẫ|Ă|Ằ|Ắ|Ặ|Ẳ|Ẵ|/g"), L"A");
	w_txt = std::regex_replace(w_txt, std::wregex(L"è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ|/g"), L"e");
	w_txt = std::regex_replace(w_txt, std::wregex(L"È|É|Ẹ|Ẻ|Ẽ|Ê|Ề|Ế|Ệ|Ể|Ễ|/g"), L"E");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ì|í|ị|ỉ|ĩ|/g"), L"i");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ì|Í|Ị|Ỉ|Ĩ|/g"), L"I");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ|/g"), L"o");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ò|Ó|Ọ|Ỏ|Õ|Ô|Ồ|Ố|Ộ|Ổ|Ỗ|Ơ|Ờ|Ớ|Ợ|Ở|Ỡ|/g"), L"O");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ|/g"), L"u");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ù|Ú|Ụ|Ủ|Ũ|Ư|Ừ|Ứ|Ự|Ử|Ữ|/g"), L"U");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ỳ|ý|ỵ|ỷ|ỹ|/g"), L"y");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ỳ|Ý|Ỵ|Ỷ|Ỹ|/g"), L"Y");
	w_txt = std::regex_replace(w_txt, std::wregex(L"đ"), L"d");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Đ"), L"D");
	string tmp(w_txt.begin(), w_txt.end());
	txt = tmp;
}
void createStopWord(vector<string>& stopWords, string path) {
	std::wstring w_content = ReadFile(path);
	string content;
	XoaDau(content, w_content);
	cout << content << endl;
	exit(0);
	char* tmp;
	tmp = new char[content.size() + 1];
	strcpy(tmp, content.c_str());
	char* token = strtok(tmp, "\n");
	string word(token);
	stopWords.push_back(word);
	cout << stopWords.back() << endl; 
	while (token != NULL)
	{
		word = token;
		stopWords.push_back(word);
		printf("%s\n", token);
		token = strtok(NULL, "\n");
	}
	delete[] tmp;
}