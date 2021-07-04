#pragma once
#include<string>

using namespace std;
struct File {
	string name;
	int size[3];
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
				cout << grams[i][j] << ' ' << gramRate[i][j] << endl;
			}
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
};

struct Data {
	int numTopic;
	vector<Topic> topics;
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
};
void Search(string input, string res);
bool addFile(string path);
bool deleteFile(string path);