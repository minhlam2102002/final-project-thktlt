#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include <fstream> 

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
string extractContent(string path) {
	ifstream wif(path);
	string res;
	return res;
}
void createMetadata(string path, vector<string> topic) {
	ofstream out(path + "\\metadata.txt");
	for (string topicName : topic) {
		out << topicName << endl;
		string topicPath = path + "\\Train\\new train\\" + topicName;
		ifstream in(topicPath + "\\index.txt");
		string content;
		while (getline(in, content)) {
			out << content << ' ';
			out << extractContent(topicPath + "\\" + content) << endl;
		}
		out << "***************\n";
		in.close();
		exit(0);
	}
	out.close();
}
int main()
{
	string root = "D:\\college\\KTLT\\final_project_ktlt\\20120018_20120316\\final_project_ktlt\\source";
	string trainPath = root + "\\Train\\new train";
	vector<string> topic = getTopic(trainPath);
	for (string topicName : topic) {
		string curTopicPath = trainPath + "\\" + topicName;
		createIndexFile(curTopicPath);
	}
	createMetadata(root, topic);
}