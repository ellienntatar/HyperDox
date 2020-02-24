#pragma once
#include <string>
#include "Document.h"
#include <vector>
#include "DocumentManager.h"

using std::string;
using std::vector;

class CommandHandler
{
public:
	CommandHandler(vector<Document>& list);
	CommandHandler();
	~CommandHandler();


	void ParseCommand(string& in);
	string Trim(const string& str);
	string toLower(string str);
	void ExecuteCommand(char commandCode, string in);
	void DisplayHelp();
	bool FindLink(vector<Link> linkList, string search, bool userSearch);

	DocumentManager doxMan;
	char CommandCode;
	vector<Document> doxList;
	bool justSearched = false;
	vector<Link> searchLinks;
};

