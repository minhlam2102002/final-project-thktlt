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
#include <algorithm>
#include "queryFunction.h"
#include "stringFunction.h"
#include "createMetadata.h"
using namespace std;

void Search(string input, string res) {

}
bool deleteFile(string path) {
	ofstream fout("deleteFile.txt", std::ofstream::out | std::ofstream::app);
	fout << extractFileName(path) << endl;
	fout.close();
	return true;
}
bool addFile(string path) {
	ofstream fout("addFile.txt", std::ofstream::out | std::ofstream::app);
	string keyWord;
	extractKeyWord(path, keyWord);
	fout << extractFileName(path) << endl;
	fout << keyWord;
	fout.close();
	return true;
}