#include "pch.h"
#include "CommandHandler.h"
#include <string>
#include <iostream>
#include <vector>
#include "Document.h"
#include <algorithm>

using namespace std;

CommandHandler::CommandHandler()
{
}

CommandHandler::CommandHandler(vector<Document>& list) 
{
	//references the list of documents so we may execute commands
	doxList = list;
}

CommandHandler::~CommandHandler()
{
}

/*
g = get document
f = find word
l = use link

*/

void CommandHandler::ParseCommand(string& in) 
{
	if (in.size() > 0) {
		//trims the input string of any extra whitespaces
		Trim(in);
		CommandCode = in.at(0);
		string parsed = toLower(in);
		//moves past the command code and then finds the command details
		if (parsed.size() > 1) {
			size_t commandDetailPos = parsed.find_first_not_of(' ', 1);
			//takes the substring that will be used when executing command
			parsed = parsed.substr(commandDetailPos);
		}
		//executes command
		ExecuteCommand(CommandCode, parsed);
	}
}

void CommandHandler::ExecuteCommand(char commandCode, string in) 
{
	int i;
	
	//if the user input the listdox command
	if (commandCode == 'l') 
	{
		cout << "Document list:" << endl << "-------------------------------------" << endl;
		//displays all documents that can be viewed
		for (i = 0; i < doxList.size(); i++)
		{
			cout << doxList.at(i).FileName << endl;
		}
	}
	//if the user is trying to get a document
	else if(commandCode == 'g')
	{
		doxMan.GetDocument(in);
	}
	//if the user is trying to find a word
	else if (commandCode == 'f') 
	{
		//finds the search in the file, then sets justSearched to true, so user may access 
		//the links that were printed
		searchLinks = doxMan.Search(in);
		doxMan.PrintLinks(searchLinks);
		justSearched = true;
	}
	//if the user is trying to find a link within the document
	else if (commandCode == 'a') 
	{
		//monitors to see if the user has just searched
		if (justSearched) 
		{
			//finds the link in search results, if link is found success is set to true
			bool success = FindLink(searchLinks, in, true);
			//if the link was a success then just searched will be set to false
			if (success) 
			{
				justSearched = false;
			}
		}
		else 
		{
			//finds the link num in the current document
			FindLink(doxMan.currDoc.FileLinks, in, false);
		}
	}
	//if the user wants the help list
	else if (commandCode == 'h')
	{
		DisplayHelp();
	}
	//if the user wants to quit
	else if (commandCode == 'q') 
	{
		exit(0);
	}
	//if user is trying to check current document stats
	else if (commandCode == 's') 
	{
		doxMan.currDoc.PrintStats();
	}
	//if the user's command failed
	else 
	{
		cout << "Invalid command! Check command list: " << endl;
		DisplayHelp();
	}
}

string CommandHandler::Trim(const string& str)
{
	//finds the first char in the string that is not a whitespace
	size_t first = str.find_first_not_of(' ');
	//if the string was only whitespaces then return the string
	if (string::npos == first)
	{
		return str;
	}
	//finds the last char that is not a whitespace
	size_t last = str.find_last_not_of(' ');
	//returns the trimmed string
	return str.substr(first, (last - first + 1));
}

//simple method to make commands not case sensitive
string CommandHandler::toLower(string str) 
{
	string outS = str;
	for (int i = 0; i < str.size(); i++) 
	{
		outS.at(i) = tolower(outS.at(i));
	}
	return outS;
}

//simple method to display commands
void CommandHandler::DisplayHelp() 
{
	cout << "Command List:" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "g (document name) - gets the document with name inputted." << endl;
	cout << "f (search word) - displays a list of occurances of search word." << endl;
	cout << "a (link number) - displays the text at the location of link number." << endl;
	cout << "l - lists all documents that can be displayed." << endl;
	cout << "h - display this list." << endl;
	cout << "q - quit the program." << endl;
	cout << "s - display current document's stats." << endl;
	cout << "-------------------------------------------------------------" << endl;
}

bool CommandHandler::FindLink(vector<Link> linkList, string search, bool userSearch) 
{
	bool isNum = true;
	//checks to see if user entered a number
	for (int i = 0; i < search.size(); i++)
		if(!(isdigit(search[i])))  isNum = false;

	
	if (isNum) {
		//gets the user's inputted link num
		int numLink = stoi(search);
		bool hasFound = false;
		for (int i = 0; i < linkList.size(); i++)
		{
			if (linkList.at(i).LinkNum == numLink)
			{
				//gets the document at the link for the user search
				if (userSearch)
				{
					string filename = linkList.at(i).FileName;
					transform(filename.begin(), filename.end(), filename.begin(), tolower);
					doxMan.GetDocument(filename);
				}
				else
				{
					//links are used differently for document links, the filename
					//of the link is stored in linktext
					doxMan.GetDocument(linkList.at(i).LinkText);
				}
				hasFound = true;
			}
		}
		//if the link could not be found then prints error message and returns false
		//so user may try again
		if (!hasFound)
		{
			cout << "Could not find link #" << search << "!" << endl;
			return false;
		}
		//returns true if the link was found
		return true;
	}
	else 
	{
		//if the user entered an alpha
		cout << "Please enter a number! Link: " << search << " is not a num." << endl;
		return false;
	}
}