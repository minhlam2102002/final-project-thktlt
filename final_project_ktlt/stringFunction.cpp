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
#include <algorithm>
#include "stringFunction.h"
#include "InOut.h"
using namespace std;

wstring idVowels = L"aAeEiIoOuUyYdD";
wstring vowels[14] = {
L"àáạảãâầấậẩẫăằắặẳẵ", L"ÀÁẠẢÃÂẦẤẬẨẪĂẰẮẶẲẴ",
L"èéẹẻẽêềếệểễ", L"ÈÉẸẺẼÊỀẾỆỂỄ",
L"ìíịỉĩ", L"ÌÍỊỈĨ",
L"òóọỏõôồốộổỗơờớợởỡ", L"ÒÓỌỎÕÔỒỐỘỔỖƠỜỚỢỞỠ",
L"ùúụủũưừứựửữ", L"ÙÚỤỦŨƯỪỨỰỬỮ",
L"ỳýỵỷỹ", L"ỲÝỴỶỸ",
L"đ", L"Đ" };

vector<string> stopWords;

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
			str[i] == '\n' || str[i] == '\'')) {
			str[i] = ' ';
		}
	}
}
void extractWord(string& content, vector<string>& words) {
	words.clear();
	stringstream ss(content);
	string word;
	while (ss >> word) {
		words.push_back(word);
	}
}
void deleteStopWord(string& content) {
	vector<string> childWords, momWords;
	extractWord(content, momWords);
	content = "";
	for (int i = 0; i < momWords.size(); i++) {
		int fr = lower_bound(stopWords.begin(), stopWords.end(), momWords[i]) - stopWords.begin();
		bool isStopWord = false;
		for (int j = fr; j < stopWords.size(); j++) {
			bool isDif = false;
			extractWord(stopWords[j], childWords);
			if (momWords[i] != childWords[0]) {
				break;
			}
			if (i + childWords.size() > momWords.size()) {
				continue;
			}
			for (int t = 0; t < childWords.size(); t++) {
				if (momWords[i + t] != childWords[t]) {
					isDif = true;
					break;
				}
			}
			if (isDif == false) {
				isStopWord = true;
				i += childWords.size() - 1;
				break;
			}
		}
		if (isStopWord == false) {
			content += momWords[i] + ' ';
		}
	}
}
string XoaDau(std::wstring& w_txt) { // XoaDau + LowerCase
	for (auto& c : w_txt) {
		for (int i = 0; i < 14; i++) {
			for (auto &v : vowels[i]) {
				if (c == v) {
					c = idVowels[i];
				}
			}
		}
	}
	string txt(w_txt.begin(), w_txt.end());
	return txt;
}
void createStopWord() {
	wstring w_content = ReadFileUTF8("source\\vietnamese-stopwords.txt");
	string content = XoaDau(w_content);
	char* tmp;
	tmp = new char[content.size() + 1];
	strcpy(tmp, content.c_str());
	char* token = strtok(tmp, "\n");
	string word = token;
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
void countAppearance(vector<string>& words, vector<string>& grams, vector<int>& rate, int type) { // count appear child in mom = res
	for (int i = 0; i < words.size() - type; i++) {
		string token;
		for (int j = i; j <= i + type; j++) {
			token += words[j] + ' ';
		}
		token.pop_back();
		grams.push_back(token);
	}
	sort(grams.begin(), grams.end());
	grams.resize(unique(grams.begin(), grams.end()) - grams.begin());
	rate.assign(grams.size(), 0);
	vector<string> gramToken;
	for (int i = 0; i < words.size(); i++) {
		int fr = lower_bound(grams.begin(), grams.end(), words[i]) - grams.begin();
		for (int j = fr; j < grams.size(); j++) {
			bool isSame = true;
			extractWord(grams[j], gramToken);
			if (words[i] != gramToken[0]) {
				break;
			}
			if (i + gramToken.size() > words.size()) {
				continue;
			}
			for (int t = 0; t < gramToken.size(); t++) {
				if (words[i + t] != gramToken[t]) {
					isSame = false;
					break;
				}
			}
			if (isSame == true) {
				rate[j]++;
			}
		}
	}
	for (int i = 0; i < rate.size(); i++) {
		rate[i] = (float)rate[i] / (words.size() - type) * 100 * 100;
	}
}