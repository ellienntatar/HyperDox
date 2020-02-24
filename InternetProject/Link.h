#pragma once
#include <string>

using std::string;
class Link
{
public:
	Link();
	Link(string fileName, int LinkNum, int position, string text);
	~Link();
	
	string PrintLink();

	string FileName;
	int LinkNum;
	int Position;
	string LinkText;
};

