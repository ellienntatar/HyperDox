#include "pch.h"
#include "DocumentManager.h"
#include <string>
#include <vector>
#include "Document.h"
#include <iostream>
#include <algorithm>

using namespace std;


DocumentManager::DocumentManager()
{
}


DocumentManager::~DocumentManager()
{
}

void DocumentManager::LoadFiles(string path, vector<string*>& list) 
{
	for (int i = 0; i < list.size(); i++) 
	{
		//creates a document
		Document file = CreateDocument(path, *list.at(i));
		//fills the document with the file's contents
		file.ParseFile();
		//puts the file at the end of the doxList
		doxList.push_back(file);
		
	}
	
}

Document DocumentManager::CreateDocument(string path, string fileName) 
{
	//creates a document and returns it
	Document doc = Document(path, fileName);
	return doc;
}

//simple setter
void DocumentManager::SetDocument(Document doc) 
{
	currDoc = doc;
}

void DocumentManager::GetDocument(string fileName) 
{
	//transform(fileName.begin(), fileName.end(), fileName.begin(), tolower);
	bool found = false;;
	for (int i = 0; i < doxList.size(); i++) 
	{
		//makes the filename not case sensitive
		string lowered = doxList.at(i).FileName;
		transform(lowered.begin(), lowered.end(), lowered.begin(), tolower);
		
		//checks to see if the user filename is current filename
		if (lowered.compare(fileName) == 0)
		{
			//sets the current document and prints text
			SetDocument(doxList.at(i));
			cout << fileName << ":" << endl;
			PrintText(doxList.at(i).FileText);
			found = true;
			break;
		}
	}
	//if the doc was not found then an error message will be printed
	if (!found)
	{
		cout << "Document '" << fileName << "' not found!" << endl;
	}
}

//returns the contents of all dox
void DocumentManager::GetAllDocuments() 
{
	for (int i = 0; i < doxList.size(); i++) 
	{
		//prints the document's name before printing it's contents
		cout << doxList.at(i).FileName << endl;
		//gets the document's text
		vector<string> fileContents = doxList.at(i).FileText;
		//iterates through FileText printing out file text
		PrintText(doxList.at(i).FileText);
		//readability spacing
		cout << endl << endl;
	}
}



void DocumentManager::PrintLinks(vector<Link> link) 
{
	if (link.size() > 0)
	{
		for (int i = 0; i < link.size(); i++)
		{
			cout << link.at(i).PrintLink() << endl;
		}
	}
	//this is for when a user is searching for something, if there are no links this will be printed
	else 
	{
		cout << "Could not find any instances your search!" << endl;
	}
}

//method to reduce duplicate code
void DocumentManager::PrintText(vector<string> list) 
{
	for (int j = 0; j < list.size(); j++)
	{
		cout << list.at(j) << endl;
	}
}

//searches all of the documents for the user's input
vector<Link> DocumentManager::Search(string search) 
{
	int anchorNum = 0;
	vector<Link> searchLinks;

	for (int i = 0; i < doxList.size(); i++) 
	{
		int pos = 0;
		for (int j = 0; j < doxList.at(i).FileText.size(); j++) 
		{
			//gets current line and makes it all lowercase and removes punctuation
			string currLine = doxList.at(i).FileText.at(j);
			transform(currLine.begin(), currLine.end(), currLine.begin(), tolower);
			remove_if(currLine.begin(), currLine.end(), ispunct);

			//finds the first occurance of search in line if there is any
			size_t occurance = currLine.find(search);
			//if the line contains search it will be added
			while (occurance != string::npos)
			{
				int exactPos = occurance + pos;
				Link newLink;
				anchorNum += 1;
				newLink = Link(doxList.at(i).FileName, anchorNum, exactPos, search);
				occurance = currLine.find(search, occurance + search.size());
				searchLinks.push_back(newLink);
			}
			pos += doxList.at(i).FileText.at(j).size();
		}
		
	}
	return searchLinks;
}

