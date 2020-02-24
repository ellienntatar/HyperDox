#pragma once
#include <string>
#include <vector>
#include "Link.h"

using std::string;
using std::vector;
class Document
{
public:
	Document();
	Document(string path, string fileName);
	~Document();
	void ParseFile();
	vector<Link> FindLinks();
	void CalculateStats();
	void PrintStats();

	string Path;
	string FileName;
	vector<string> FileText;
	vector<Link> FileLinks;

	int NumWords;
	float AvgWords;
	int NumLinks;
};

