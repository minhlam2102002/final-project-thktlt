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
#include "InOut.h"
#include "stringFunction.h"

using namespace std;
namespace fs = std::filesystem;

string extractFileName(string path) {
	string res;
	for (int i = path.size() - 1; path[i] != '\\'; i--) {
		res += path[i];
	}
	reverse(res.begin(), res.end());
	return res;
}
void getTopic(string path, vector<string> &topic) {
	for (auto& file : fs::directory_iterator(path)) {
		fs::path p = file.path();
		topic.push_back(extractFileName(p.string()));
	}
}
void createIndexFile(string root, string trainPath, vector<string> topic) {
	ofstream out(root + "\\index.txt");
	out << topic.size() << endl;
	for (string topicName : topic) {
		out << topicName << endl;
		vector<string> files;
		for (auto& file : fs::directory_iterator(trainPath + "\\" + topicName)) {
			fs::path p = file.path();
			files.push_back(extractFileName(p.string()));
		}
		out << files.size() << endl;
		for (string cur : files) {
			out << cur << endl;
		}

	}
	out.close();
}

string extractKeyWord(string path, vector<string>& stopWords) { // exctract file at path
	//su dung tien xu ly :vvvv
	string keyWord;
	string content = XoaDau(ReadFileUTF16(path));
	lowerCase(content);
	fixWord(content);
	deleteStopWord(content, stopWords);
	//exit(0);
	for (int i = 0; i < 1; i++) {
		keyWord += content[i];
	}
	return keyWord;
}

void createMetadata(string root, string trainPath) {
	vector<string> stopWords;
	createStopWord(stopWords);
	ifstream in(root + "\\index.txt");
	ofstream out(root + "\\metadata.txt");
	int numTopics, numFiles;
	in >> numTopics;
	in.ignore();
	out << numTopics << endl;
	string curTopic, curFile;
	while (numTopics--) {
		getline(in, curTopic);
		out << curTopic << endl;
		in >> numFiles;
		out << numFiles << endl;
		in.ignore();
		while (numFiles--) {
			getline(in, curFile);
			out << curFile << endl;
			out << extractKeyWord(trainPath + "\\" + curTopic + "\\" + curFile, stopWords);
			return;
		}
	}
	in.close();
	out.close();
}
int main(){
	//InOut();
	string root = "D:\\college\\KTLT\\final_project_ktlt\\20120018_20120316\\final_project_ktlt\\source";
	string trainPath = root + "\\Train\\new train";
	vector<string> topic;
	getTopic(trainPath, topic);
	createIndexFile(root, trainPath, topic);
	createMetadata(root, trainPath);
}