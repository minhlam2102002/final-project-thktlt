#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>
#include <utility>
#include <fstream> 
#include "InOut.h"
#include "stringFunction.h"
#include <iomanip>
//#include <Windows.h>
//#include <conio.h>

using namespace std;
namespace fs = std::filesystem;

struct File {
	string name;
	bool isDel = false;
	int size[3] = { 0 };
	int appear[3] = { 0 };
	vector<string> grams[3];
	vector<int> rate[3];
	void Read(ifstream& fin) {
		getline(fin, name);
		for (int i = 0; i < 3; i++) {
			fin >> size[i];
			grams[i].resize(size[i]);
			rate[i].resize(size[i]);
			for (int j = 0; j < size[i]; j++) {
				string token;
				grams[i][j] = "";
				for (int w = 0; w <= i; w++) {
					fin >> token;
					grams[i][j] += token + ' ';
				}
				grams[i][j].pop_back();
				fin >> rate[i][j];
			}
		}
	}
	void Print(ofstream& fout) {
		if (isDel == true) {
			return;
		}
		fout << name << endl;
		for (int i = 0; i < 3; i++) {
			fout << size[i] << endl;
			for (int j = 0; j < grams[i].size(); j++) {
				fout << grams[i][j] << ' ' << rate[i][j] << endl;
			}
		}
	}
	void compare(string &gram, int &type) {
		if (isDel == true) {
			return;
		}
		int pos = lower_bound(grams[type].begin(), grams[type].end(), gram) - grams[type].begin();
		if (grams[type][pos] == gram) {
			appear[type] += rate[type][pos];
		}
	}
	void search(vector<pair<string, int>>& res) {
		if (isDel == true) {
			return;
		}
		int sum = appear[0] + appear[1] + appear[2];
		appear[0] = 0;
		appear[1] = 0;
		appear[2] = 0;
		if (sum > 0) {
			res.push_back(make_pair(name, sum));
		}
	}
	void Train(string trainPath) {
		extractKeyWord(trainPath, grams, rate);
		for (int i = 0; i < 3; i++) {
			size[i] = grams[i].size();
		}
	}
};
struct Topic {
	int numFiles = 0;
	int cntDel = 0;
	string name;
	vector<File> files;
	void Read(ifstream& fin) {
		getline(fin, name);
		fin >> numFiles;
		files.resize(numFiles);
		for (int i = 0; i < files.size(); i++) {
			fin.ignore();
			files[i].Read(fin);
		}
	}
	void Print(ofstream& fout) {
		fout << name << endl;
		fout << numFiles - cntDel << endl;
		for (int i = 0; i < files.size(); i++) {
			files[i].Print(fout);
		}
	}
	int findFile(string file) {
		int l = 0, r = files.size() - 1;
		while (l <= r) {
			int mid = l + (r - l) / 2;
			if (files[mid].name == file) {
				return mid;
			}
			if (files[mid].name < file) {
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		return -1;
	}
	void compare(string &gram, int &type) {
		for (int i = 0; i < files.size(); i++) {
			files[i].compare(gram, type);
		}
	}

	void compute(vector<pair<string, int>>& res) {
		for (int i = 0; i < files.size(); i++) {
			files[i].search(res);
		}
	}
	void Train(string trainPath) {
		for (int i = 0; i < files.size(); i++) {
			files[i].Train(trainPath + "\\" + name + "\\" + files[i].name);
			if (i % 10 == 0) {
				float percent = 1.0 * i / (int)files.size() * 100;
				if (percent < 10) {
					cout << "0";
				}
				cout << fixed << setprecision(2) << percent << "%\n";
				//GoTo(1, 30);
			}
		}
	}
};

struct Data {
	int numTopic;
	vector<Topic> topics;
	void getTopic(string path) {
		Topic tmp;
		for (auto& file : fs::directory_iterator(path)) {
			fs::path p = file.path();
			tmp.name = extractFileName(p.string());
			topics.push_back(tmp);
		}
		tmp.name = "Other";
		topics.push_back(tmp);
		numTopic = topics.size();
	}
	void getIndex(string trainPath) {
		getTopic(trainPath);
		for (int i = 0; i < topics.size() - 1; i++) {
			File tmp;
			for (auto& file : fs::directory_iterator(trainPath + "\\" + topics[i].name)) {
				fs::path p = file.path();
				tmp.name = extractFileName(p.string());
				topics[i].files.push_back(tmp);
			}
			topics[i].numFiles = topics[i].files.size();
		}
	}
	void Train(string trainPath) {
		getIndex(trainPath);
		for (int i = 0; i < topics.size(); i++) {
			cout << "Training " << topics[i].name;
			for(int j = topics[i].name.size(); j < 20; j++) cout << '.';
			topics[i].Train(trainPath);
			cout << "100.00%" << endl;
		}
	}
	void Read(string path) {
		ifstream fin(path);
		fin >> numTopic;
		topics.resize(numTopic);
		for (int i = 0; i < topics.size(); i++) {
			fin.ignore();
			topics[i].Read(fin);
			//return; // read 1 file
		}
		fin.close();
	}
	string deleteFile(string path) {
		path = extractFileName(path);
		for (int i = 0; i < topics.size(); i++) {
			int pos = topics[i].findFile(path);
			if (pos != -1) {
				topics[i].cntDel++;
				topics[i].files[pos].isDel = true;
				return "Deleted done         ";
			}
		}
		return "This file not in data";
	}
	string addFile(string path) {
		ifstream f(path);
		if (f.good() == false) {
			return "Can not open file        ";
		}
		f.close();
		string name = extractFileName(path);
		for (int i = 0; i < topics.size(); i++) {
			int pos = topics[i].findFile(name);
			if (pos != -1) {
				if (topics[i].files[pos].isDel == true) {
					topics[i].files[pos].isDel = false;
					topics[i].cntDel--;
				}
				else {
					return "This file is existed in data";
				}
			}
		}
		File tmp;
		tmp.name = name;
		tmp.Train(path);
		topics.back().numFiles++;
		topics.back().files.push_back(tmp);
		return "Add Done            ";
	}
	void Print(string path) {
		ofstream fout(path);
		fout << numTopic << endl;
		for (int i = 0; i < topics.size(); i++) {
			topics[i].Print(fout);
			//return; // read 1 file
		}
		fout.close();
	}
	void compare(string &gram, int &type) {
		for (int i = 0; i < topics.size(); i++) {
			topics[i].compare(gram, type);
		}
	}
	void compute(vector<pair<string, int>> &res) {
		for (int i = 0; i < topics.size(); i++) {
			topics[i].compute(res);
		}
	}
	void Search(string& input, vector<pair<string, int>>& res) {
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
				compare(token, type);
			}
		}
		compute(res);
		sort(res.begin(), res.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
			return a.second > b.second;
		});
	}
};