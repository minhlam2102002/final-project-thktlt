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

using namespace std;
namespace fs = std::filesystem;

vector<string> getTopic(string path) {
	vector<string> topic;
	for (auto& file : fs::directory_iterator(path)) {
		fs::path p = file.path();
		topic.push_back(extractFileName(p.string()));
	}
	return topic;
}
void createIndexFile(string path) {
	ofstream out(path + "\\index.txt");
	for (auto& file : fs::directory_iterator(path)) {
		fs::path p = file.path();
		if (p.string() != "index.txt") {
			out << extractFileName(p.string()) << endl;
		}
	}
	out.close();
}
void createMetadata(std::wstring path, std::wstring topic) {
	std::wstring data;
	string topicPath = path + "\\Train\\new train\\" + topicName;
	ifstream in(topicPath + "\\index.txt");
	vector<string> filename;
	while (getline(in, content)) {
		filename.push_back()
	}
}

int main()
{
	InOut();
	string root = "D:\\college\\KTLT\\final_project_ktlt\\20120018_20120316\\final_project_ktlt\\source";
	string trainPath = root + "\\Train\\new train";
	std::wstring wroot(root.begin(), root.end());
	vector<string> topic = getTopic(trainPath);
	for (string topicName : topic) {
		string curTopicPath = trainPath + "\\" + topicName;
		createIndexFile(curTopicPath);
	}
	for (string topicName : topic) {
		std::wstring wtopic(topicName.begin(), topicName.end());
		createMetadata(wroot, wtopic);
	}
	std::wstring finalPath = L"userinfo-c++.txt";
	std::wstring outPath = L"Testing.out";
	PrintWord(outPath, ReadWord(finalPath));
}