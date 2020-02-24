#pragma once
#include <string>
#include <vector>
#include "Document.h"
#include "DocumentManager.h"
#include "CommandHandler.h"

using std::string;
using std::vector;
class Navigator
{
public:
	Navigator();
	Navigator(string& dirPath);
	~Navigator();

	void FindFiles(string& dirPath, vector<string*>& fileList);
	//void DocumentManager();
	//void CommandHandler();

	CommandHandler comHand;
	DocumentManager doxMan = DocumentManager();
	string fileDirectory;
	vector<string*> fileList;

};

