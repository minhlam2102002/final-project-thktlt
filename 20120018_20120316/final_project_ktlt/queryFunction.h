#pragma once
#include<string>
#include "queryFunction.h"
#include "InOut.h"
#include "stringFunction.h"
#include "createMetadata.h"
using namespace std;

struct File {
	string name;
	int size[3];
	int appear[3] = { 0 };
	vector<string> grams[3];
	vector<int> gramRate[3];
	void Read(ifstream& fin) {
		fin.ignore();
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
		fout << name << endl;
		for (int i = 0; i < 3; i++) {
			fout << size[i] << endl;
			for (int j = 0; j < size[i]; j++) {
				fout << grams[i][j] << ' ' << gramRate[i][j] << endl;
			}
		}
	}
	void compare(string &gram, int &type) {
		int pos = lower_bound(grams[type].begin(), grams[type].end(), gram) - grams[type].begin();
		if (grams[type][pos] == gram) {
			appear[type] += gramRate[type][pos];
		}
	}
	void search(vector<pair<string, int>>& res) {
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
	string name;
	vector<File> files;
	void Read(ifstream& fin) {
		fin.ignore();
		getline(fin, name);
		fin >> numFiles;
		files.resize(numFiles);
		for (int i = 0; i < numFiles; i++) {
			files[i].Read(fin);
			//return; // read 1 file
		}
	}
	void Print(ofstream& fout) {
		fout << name << endl;
		fout << numFiles << endl;
		for (int i = 0; i < numFiles; i++) {
			files[i].Print(fout);
			//return;// 1file
		}
	}
	void compare(string &gram, int &type) {
		for (int i = 0; i < numFiles; i++) {
			files[i].compare(gram, type);
		}
	}

	void search(vector<pair<string, int>>& res) {
		for (int i = 0; i < numFiles; i++) {
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
		for (int i = 0; i < numTopic; i++) {
			topics[i].Read(fin);
			//return; // read 1 file
		}
		fin.close();
	}
	void deleteFile(string path) {
		deleted.push_back(extractFileName(path));
	}
	void addFile(string path) {
		ofstream fout("addFile.txt");
		string keyWords;
		extractKeyWord(path, keyWords);
		fout << extractFileName(path) << endl;
		fout << keyWords;
		fout.close();
		ifstream fin("addFile.txt");
		File tmp;
		tmp.Read(fin);
		topics.back().files.push_back(tmp);
		fin.close();
	}
	void Print(string path) {
		ofstream fout(path);
		fout << numTopic << endl;
		for (int i = 0; i < numTopic; i++) {
			topics[i].Print(fout);
			//return; // read 1 file
		}
		fout.close();
	}
	void compare(string &gram, int &type) {
		for (int i = 0; i < numTopic; i++) {
			topics[i].compare(gram, type);
		}
	}
	void search(vector<pair<string, int>> &res) {
		for (int i = 0; i < numTopic; i++) {
			topics[i].search(res);
		}
	}
};
void Search(Data& metadata, string& input, vector<pair<string, int>> &res);