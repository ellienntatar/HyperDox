#include "pch.h"
#include "Link.h"
#include <string>

using namespace std;

Link::Link()
{
}

//sets the link's fields
Link::Link(string fileName, int linkNum, int position, string text)
{
	FileName = fileName;
	LinkNum = linkNum;
	Position = position;
	LinkText = text;
}

Link::~Link()
{
}

//simple method to format the links
string Link::PrintLink() 
{
	return "[" + to_string(LinkNum) + "] |" + FileName + "|" +  to_string(Position) + ":" + LinkText;
}