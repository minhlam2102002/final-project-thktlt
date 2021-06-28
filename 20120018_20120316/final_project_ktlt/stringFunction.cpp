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
			(str[i] >= '0' && str[i] <= '9') ||
			str[i] == '\n')) {
			str[i] = ' ';
		}
	}
}
void extractWord(string &content, vector<string>& words) {
	words.clear();
	stringstream ss(content);
	string word;
	while (ss >> word) {
		words.push_back(word);
	}
}
void deleteStopWord(string &content, vector<string>& stopWords) {
	vector<string> childWords, momWords;
	extractWord(content, momWords);
	content = "";
	for (int i = 0; i < momWords.size(); i++) {
		int fr = lower_bound(stopWords.begin(), stopWords.end(), momWords[i]) - stopWords.begin();
		int to = upper_bound(stopWords.begin(), stopWords.end(), momWords[i]) - stopWords.begin();
		bool isDif = false;
		for(int j = fr; j < to; j++){
			if (i + childWords.size() > momWords.size()) {
				continue;
			}
			extractWord(stopWords[j], childWords);
			for (int j = 0; j < childWords.size(); j++) {
				if (momWords[i + j] != childWords[j]) {
					isDif = true;
					break;
				}
			}
			if (isDif == false) {
				i += childWords.size() - 1;
				break;
			}
		}
		if (isDif == true || fr == to) {
			content += momWords[i] + ' ';
		}
	}

}
string XoaDau(std::wstring &w_txt) { // XoaDau + LowerCase
	wstring id = L"aAeEiIoOuUyYdD";
	wstring vowels[14];
	vowels[0] = L"àáạảãâầấậẩẫăằắặẳẵ";
	vowels[1] = L"ÀÁẠẢÃÂẦẤẬẨẪĂẰẮẶẲẴ";
	vowels[2] = L"èéẹẻẽêềếệểễ";
	vowels[3] = L"ÈÉẸẺẼÊỀẾỆỂỄ";
	vowels[4] = L"ìíịỉĩ";
	vowels[5] = L"ÌÍỊỈĨ";
	vowels[6] = L"òóọỏõôồốộổỗơờớợởỡ";
	vowels[7] = L"ÒÓỌỎÕÔỒỐỘỔỖƠỜỚỢỞỠ";
	vowels[8] = L"ùúụủũưừứựửữ";
	vowels[9] = L"ÙÚỤỦŨƯỪỨỰỬỮ";
	vowels[10] = L"ỳýỵỷỹ";
	vowels[11] = L"ỲÝỴỶỸ";
	vowels[12] = L"đ";
	vowels[13] = L"Đ";
	for (auto &c : w_txt) {
		for (int i = 0; i < 14; i++) {
			for (auto v : vowels[i]) {
				if (c == v) {
					c = id[i];
				}
			}
		}
	}
	string txt(w_txt.begin(), w_txt.end());
	return txt;
}
void createStopWord(vector<string>& stopWords) {
	wstring w_content = ReadFileUTF8("vietnamese-stopwords.txt");
	string content = XoaDau(w_content);
	char* tmp;
	tmp = new char[content.size() + 1];
	strcpy(tmp, content.c_str());
	char* token = strtok(tmp, "\n");
	string word(token);
	stopWords.push_back(word);
	while (token != NULL)
	{
		word = token;
		stopWords.push_back(word);
		token = strtok(NULL, "\n");
	}
	delete[] tmp;
	sort(stopWords.begin(), stopWords.end());
}
int countAppearance(string &mom, string &child) {
	string S = child + "*" + mom;
	int n = S.size();
	vector<int> Z(n);
	int L = 0, R = 0;
	Z[0] = n;
	for (int i = 1; i < n; i++) {
		if (i > R){
			L = R = i;
			while (R < n && S[R] == S[R - L]) R++;
			Z[i] = R - L; R--;
		}
		else{
			int k = i - L;
			if (Z[k] < R - i + 1) Z[i] = Z[k];
			else{
				L = i;
				while (R < n && S[R] == S[R - L]) R++;
				Z[i] = R - L; R--;
			}
		}
	}
	int cnt = 0;
	for (int i = child.size(); i < n; i++) {
		if (Z[i] == child.size()) {
			cnt++;
		}
	}
	return cnt;
}