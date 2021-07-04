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
#include <utility>
#include "InOut.h"
#include "stringFunction.h"
#include "createMetadata.h"
#include "queryFunction.h"

#include <ctime>
#include <ratio>
#include <chrono>
using namespace std::chrono;

using namespace std;
namespace fs = std::filesystem;


int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	string root = "D:\\college\\KTLT\\final_project_ktlt\\20120018_20120316\\final_project_ktlt\\source";
	string trainPath = root + "\\Train\\new train";
	Data metadata;
	high_resolution_clock::time_point Begin = high_resolution_clock::now();
	createMetadata(root, trainPath);
	metadata.Read(root + "\\metadata.txt");
	//metadata.Print(root + "\\metadata.txt");
	string input = "am nhac";
	vector<pair<string, int>> res;
	Search(metadata, input, res);
	high_resolution_clock::time_point End = high_resolution_clock::now();
	duration<double, std::milli> time_span = End - Begin;
	cout << "All Process took " << time_span.count() << " milliseconds.";
	//addFile("AN_TN_ (878).txt");
	//deleteFile("AN_TN_ (878).txt");
	return 0;
	return 0;
	cout << endl << endl;
}