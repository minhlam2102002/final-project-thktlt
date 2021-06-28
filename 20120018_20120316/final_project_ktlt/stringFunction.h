#pragma once

using namespace std;
void lowerCase(string& str);
void fixWord(string& str);
void extractWord(string& content, vector<string>& words);
void deleteStopWord(string& content, vector<string>& stopWords);
string XoaDau(std::wstring &w_txt);
void createStopWord(vector<string>& stopWords); 
void countAppearance(vector<string>& words, vector<string>& grams, vector<int>& rate, int type);
