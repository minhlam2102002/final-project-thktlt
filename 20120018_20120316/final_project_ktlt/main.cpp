#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS_

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
void createMetadata(std::wstring path, std::wstring topic) {
//	std::wstring data;
//	string topicPath = path + "\\Train\\new train\\" + topicName;
//	ifstream in(topicPath + "\\index.txt");
//	string content;
//	while (getline(in, content)) {
//		out << content << ' ';
//		out << extractContent(topicPath + "\\" + content) << endl;
//	}
//	exit(0);
//}
//out.close();
}
void loverCase(string &str){
    for(int i =0;i<strlen(str.c_str());i++){
        str[i] = tolower(str[i]);
    }
	// được xài hàm có sẵn khum đó :>
}
void fixWord(string &str){
	for(int i =0;i < strlen(str.c_str);i++){
		if(str[i] == "," || str[i] == "." || str[i] == "/" || str[i] == "?" 
		|| str[i] == ":" || str[i] == ";"||str[i] == "-"||str[i] == "!" 
		|| str[i] == "\"" || str[i] == "="){
			// thay bang khoang trang de tach token
			str[i] == " ";
		}
	}
}
void extractWord(string content, vector<string> &words) {
	stringstream ss(content);
	string word;
	while (ss >> word) {
		words.push_back(word);
	}
}
bool deleteStopWord(vector<string> words, vector<string>& stopWords){

}
void createStopWord(vector<string> &stopWords, std::wstring path) {
	std::wstring w_content = ReadWord(path);
	string content = XoaDau(w_content);
	char* tmp;
	tmp = new char[content.size() + 1];
	strcpy(tmp, content.c_str());
	char* token = strtok(tmp, "\n");
	string word(token);
	stopWords.push_back(word);
	while (token != NULL)
	{
		word = token;
		stopWords.push_back(word);
		printf("%s\n", token);
		token = strtok(NULL, "\n");
	}
	delete[] tmp;
}

string XoaDau(std::wstring w_txt) {
	w_txt = std::regex_replace(w_txt, std::wregex(L"à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ|/g"), L"a");
	w_txt = std::regex_replace(w_txt, std::wregex(L"À|Á|Ạ|Ả|Ã|Â|Ầ|Ấ|Ậ|Ẩ|Ẫ|Ă|Ằ|Ắ|Ặ|Ẳ|Ẵ|/g"), L"A");
	w_txt = std::regex_replace(w_txt, std::wregex(L"è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ|/g"), L"e");
	w_txt = std::regex_replace(w_txt, std::wregex(L"È|É|Ẹ|Ẻ|Ẽ|Ê|Ề|Ế|Ệ|Ể|Ễ|/g"), L"E");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ì|í|ị|ỉ|ĩ|/g"), L"i");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ì|Í|Ị|Ỉ|Ĩ|/g"), L"I");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ|/g"), L"o");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ò|Ó|Ọ|Ỏ|Õ|Ô|Ồ|Ố|Ộ|Ổ|Ỗ|Ơ|Ờ|Ớ|Ợ|Ở|Ỡ|/g"), L"O");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ|/g"), L"u");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ù|Ú|Ụ|Ủ|Ũ|Ư|Ừ|Ứ|Ự|Ử|Ữ|/g"), L"U");
	w_txt = std::regex_replace(w_txt, std::wregex(L"ỳ|ý|ỵ|ỷ|ỹ|/g"), L"y");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Ỳ|Ý|Ỵ|Ỷ|Ỹ|/g"), L"Y");
	w_txt = std::regex_replace(w_txt, std::wregex(L"đ"), L"d");
	w_txt = std::regex_replace(w_txt, std::wregex(L"Đ"), L"D");
	string s_txt(w_txt.begin(), w_txt.end());
	return s_txt;
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