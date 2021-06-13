#include<iostream>
#include<string>
#include<vector>
#include <filesystem>

using namespace std; 
namespace fs = std::filesystem;


void Search(string input) {

}
string extractFileName(string path) {
	string res;
	for (int i = path.size() - 1; path[i] != '\\'; i--) {
		res += path[i];
	}
	reverse(res.begin(), res.end());
	return res;
}
void createIndexFile(string path) {
	vector<string> topic;
	for (auto& file : fs::directory_iterator(path)) {
		fs::path p = file.path();
		topic.push_back(extractFileName(p.string()));
	}
	for (string file : topic) {
		cout << file << endl;
	}
}
void createMetadata(string path) {

}
int main()
{
	string root = "C:\\Users\\MINH LAM\\source\\repos\\20120018_20120316\\final_project_ktlt\\source";
	string trainPath = root + "\\Train\\new train";
	createIndexFile(trainPath);
}