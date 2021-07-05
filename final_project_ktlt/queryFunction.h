#pragma once
#include <string>
#include <fstream>
#include "queryFunction.h"
#include "InOut.h"
#include "stringFunction.h"
#include "createMetadata.h"
using namespace std;

struct File {
	string name;
	bool isDel = false;
	int size[3];
	int appear[3] = { 0 };
	vector<string> grams[3];
	vector<int> gramRate[3];
	void Read(ifstream& fin) {
		getline(fin, name);
		for (int i = 0; i < 3; i++) {
			fin >> size[i];
			grams[i].resize(size[i]);
			gramRate[i].resize(size[i]);
			for (int j = 0; j < size[i]; j++) {
				string token;
				for (int w = 0; w <= i; w++) {
					fin >> token;
					grams[i][j] += token + ' ';
				}
				grams[i][j].pop_back();
				fin >> gramRate[i][j];
				//cout << grams[i][j] << ' ' << gramRate[i][j] << endl;
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
			for (int j = 0; j < size[i]; j++) {
				fout << grams[i][j] << ' ' << gramRate[i][j] << endl;
			}
		}
	}
	void compare(string &gram, int &type) {
		if (isDel == true) {
			return;
		}
		int pos = lower_bound(grams[type].begin(), grams[type].end(), gram) - grams[type].begin();
		if (grams[type][pos] == gram) {
			appear[type] += gramRate[type][pos];
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
			//return; // read 1 file
		}
	}
	void Print(ofstream& fout) {
		fout << name << endl;
		fout << numFiles - cntDel << endl;
		for (int i = 0; i < files.size(); i++) {
			files[i].Print(fout);
			//return;// 1file
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

	void search(vector<pair<string, int>>& res) {
		for (int i = 0; i < files.size(); i++) {
			files[i].search(res);
		}
	}
};

struct Data {
	int numTopic;
	vector<Topic> topics;
	vector<string> deleted;
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
		if(f.good() == false){
			return "Can not open file        ";
		}
		f.close();
		string name = extractFileName(path);
		for (int i = 0; i < topics.size(); i++) {
			int pos = topics[i].findFile(name);
			if (pos != -1) {
				return "This file is existed in data";
			}
		}
		ofstream fout("addFile.txt");
		//return "*";
		string keyWords;
		extractKeyWord(path, keyWords);
		fout << name << endl;
		fout << keyWords;
		fout.close();
		ifstream fin("addFile.txt");
		File tmp;
		tmp.Read(fin);
		topics.back().files.push_back(tmp);
		topics.back().numFiles++;
		fin.close();
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
	void search(vector<pair<string, int>> &res) {
		for (int i = 0; i < topics.size(); i++) {
			topics[i].search(res);
		}
	}
};
void Search(Data& metadata, string& input, vector<pair<string, int>> &res);