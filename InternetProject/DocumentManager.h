#pragma once
#include <string>
#include <vector>
#include "Document.h"
#include <iostream>

using std::vector;
using std::string;

class DocumentManager
{
public:
	DocumentManager();
	~DocumentManager();

	void LoadFiles(string path, vector<string*>& list);
	Document CreateDocument(string path, string fileName);

	void SetDocument(Document doc);
	void GetDocument(string fileName);
	void GetAllDocuments();
	void PrintText(vector<string> list);
	void PrintLinks(vector<Link> list);
	vector<Link> Search(string search);

	Document currDoc;
	vector<Document> doxList;
};

