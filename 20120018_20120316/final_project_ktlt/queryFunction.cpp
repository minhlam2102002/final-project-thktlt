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
#include "queryFunction.h"
#include "InOut.h"
#include "stringFunction.h"
#include "createMetadata.h"
using namespace std;

void Search(Data &metadata, string &input, vector<pair<string, int>> &res) {
	fixWord(input);
	lowerCase(input);
	string tmp = input;
	deleteStopWord(tmp);
	if (tmp.size() > 0) {
		input = tmp;
	}
	vector<string> words;
	extractWord(input, words);
	for (int type = 0; type < min(3, (int)words.size()); type++) {
		vector<string> gram;
		for (int i = 0; i < words.size() - type; i++) {
			string token;
			for (int j = i; j <= i + type; j++) {
				token += words[j] + ' ';
			}
			token.pop_back();
			metadata.compare(token, type);
		}
	}
	metadata.search(res);
	sort(res.begin(), res.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
		return a.second > b.second;
	});
	cout << input << endl;
	for (int i = 0; i < min((int)25, (int)res.size()); i++) {
		cout << res[i].first << ' ' << res[i].second << endl;
	}
}
