// InternetProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include "Navigator.h"
#include "Document.h"
#include "DocumentManager.h"
#include "Link.h"

// TODO: Find a set of files
// class Navigator()
// CommandLineInterpreter
// FindFiles
// DocumentManager()
// CommandHandler()

// class CommandHandler
// ParseCommand
// ExecuteCommand
// CommandList
// DisplayHelp

// class DocumentManager()
// LoadFiles(string path, vector<string>& list)
// CreateDocument(string filename)
// SetCurrentDoc()
// GetCurrentDoc()
// GetAllDocuments()
// SearchIndex()

// class Document()
// ParseFile()
// string Path
// string FileName
// vector<string>
// vector<Link>

// class Link()
// string FileName
// int Position
// string LinkText

//TODO: Load each file
// TODO: identify anchors, links, words
// build statistics
// create a search index

//Display a file to the user
// Show links
// Allow browsing

//Show stats for a file

//Allow search

//Show help

using namespace std;

void FindDoxFilesInPath(string& dirPath, vector<string*>& fileList) {
	string rootFolderPath = dirPath;
	string fullPath = dirPath + "/*.dox";

	_finddata_t data;
	intptr_t ff = _findfirst(fullPath.c_str(), &data);
	if (ff != -1) 
	{
		int res = 0;
		while(res != -1)
		{
			fileList.push_back(new string(data.name));
			res = _findnext(ff, &data);
		}

		_findclose(ff);
	}
}


int main()
{
	Navigator n;
	bool pathFound = true;

	string inputPath;
	cout << "Enter a path or enter 'default' to use default path." << endl;
	getline(cin, inputPath);

	//if the user inputs default then default path will be used
	if (inputPath.compare("default") == 0)
		inputPath = "..\\docFiles";
	
	//uses the path the user inputs
	n = Navigator(inputPath);	

	//displays all dox and commands
	n.doxMan.GetAllDocuments();
	n.comHand.DisplayHelp();
	
	while (true) 
	{
		string input;
		getline(cin, input);
		n.comHand.ParseCommand(input);
	}

	
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
