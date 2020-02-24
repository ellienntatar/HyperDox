#include "pch.h"
#include "Navigator.h"
#include "DocumentManager.h"
#include <io.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include "CommandHandler.h"

using namespace std;

Navigator::Navigator()
{
}

Navigator::Navigator(string& dirPath) 
{
	//finds the files we need upon construction
	FindFiles(dirPath, fileList);
	//loads them
	doxMan.LoadFiles(dirPath, fileList);
	//allows us to use document manager methods within commandhandler
	comHand = CommandHandler(doxMan.doxList);
	comHand.doxMan = doxMan;

}


Navigator::~Navigator()
{
}

void Navigator::FindFiles(string& dirPath, vector<string*>& fileList)
{
	string rootFolderPath = dirPath;
	string fullPath = dirPath + "/*.dox";

	_finddata_t data;
	intptr_t ff = _findfirst(fullPath.c_str(), &data);
	if (ff != -1)
	{
		int res = 0;
		while (res != -1)
		{
			fileList.push_back(new string(data.name));
			res = _findnext(ff, &data);
		}

		_findclose(ff);
	}
}

//void Navigator::DocumentManager() 
//{
//
//}