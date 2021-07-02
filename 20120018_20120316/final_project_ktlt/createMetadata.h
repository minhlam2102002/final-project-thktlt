#pragma once
#include<vector>
#include<string>
using namespace std;

string extractFileName(string path);
void getTopic(string path, vector<string>& topic);
void createIndexFile(string root, string trainPath, vector<string>& topic);
void extractKeyWord(string path, string& keyWords);
void createMetadata(string root, string trainPath);