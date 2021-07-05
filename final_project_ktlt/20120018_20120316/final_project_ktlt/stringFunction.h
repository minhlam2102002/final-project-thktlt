#pragma once
#include<vector>
#include<string>
using namespace std;
string extractFileName(string path);
void lowerCase(string& str);
void fixWord(string& str);
void extractWord(string& content, vector<string>& words);
void deleteStopWord(string& content);
string XoaDau(std::wstring& w_txt);
void createStopWord();
void countAppearance(vector<string>& words, vector<string>& grams, vector<int>& rate, int type);
void extractKeyWord(string path, vector<string> grams[3], vector<int> rate[3]);