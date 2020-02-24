#include "pch.h"
#include "Document.h"
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "Link.h"
#include <iostream>

using namespace std;

Document::Document()
{
}

Document::Document(string path, string fileName) 
{
	//sets members
	Path = path;
	FileName = fileName;
}

void Document::ParseFile() 
{	
	ifstream fileInput;
	//opens the file
	fileInput.open(Path+"\\"+ FileName);
	string line;
	//gets all of the lines in the file and puts them into our string vector
	int i = 0;
	while (getline(fileInput, line))
	{
		//puts the current line in the file at the end of FileText
		FileText.push_back(line);
		i++;
	}
	//searches the file for links
	FileLinks = FindLinks();

	CalculateStats();

	fileInput.close();
}


Document::~Document()
{
}

void Document::CalculateStats() 
{
	//sets document stats
	NumLinks = FileLinks.size();
	int numWords = 0;
	int length = 0;
	
	for (int i = 0; i < FileText.size(); i++) 
	{
		string str = FileText.at(i);
		char prev = ' ';
		int len = 0;
		for (unsigned int i = 0; i < str.size(); i++) {

			//checks to see if current char is not a space, and if the previous char was a space, numWords will increment
			if (isalpha(str[i])) {
				if (isspace(prev)) {
					numWords++;
				}
				len++;
			}

			//moves prev up one char
			prev = str[i];
		}
		length += len;
	}
	NumWords = numWords;
	AvgWords = (double) length / numWords;
}

void Document::PrintStats() 
{
	cout << "Number of words: " << NumWords << endl;
	cout << "Average word length: " << AvgWords << endl;
	cout << "Number of links: " << NumLinks << endl;
}

//simple method to search file for a string
vector<Link> Document::FindLinks() 
{
	int pos = 0;
	int anchorNum = 0;
	vector<Link> results;
	string search = "|";
	for (int i = 0; i < FileText.size(); i++) 
	{
		//finds the first occurance of search in line if there is any
		size_t occurance = FileText.at(i).find(search);
		//if the line contains search it will be added
		while(occurance != string::npos)
		{
			int exactPos = occurance + pos;
			Link newLink;
				
			anchorNum += 1;
			//finds the closing brackets and the gets the string in between the brackets
			size_t endOccurance = FileText.at(i).find(search, occurance + 1);

			//the plus 1s and minus 1s in this line are to get rid of the "|"s
			string linkText = FileText.at(i).substr(occurance + 1, endOccurance - occurance - 1);
			size_t docNameEnd = linkText.find(":");
			linkText = linkText.substr(0, docNameEnd);

			newLink = Link(FileName, anchorNum, exactPos, linkText);

			//stuff to replace inline text and stuff to increment past the next |
			FileText.at(i).replace(occurance + 1, endOccurance - occurance - 1, to_string(anchorNum));

			//sets occurance to the first char after ending link | 
			//must reset endOccurance due to the actual end of link's
			//position being changed because it was replaced
			endOccurance = FileText.at(i).find(search, occurance + 1);
			occurance = FileText.at(i).find(search, endOccurance + 1);
			
			results.push_back(newLink);
		}
		//adds the length of the current string to pos number 
		pos += FileText.at(i).size();
	}
	return results;
}

