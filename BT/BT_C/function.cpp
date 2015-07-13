#include "function.h"
#include <iostream>

void process(std::string filename)
{
	if ("" == filename)
	{
		std::cout << "filename is null" << std::endl;
		exit(0);
	}
	std::ifstream file(filename.c_str());
	SLDictionary *pD = new SLDictionary;
	int ch = file.get();
	praseDictionary(file, pD);
}

void praseInterger(std::ifstream &file, SLInterger *pInt)
{
	std::string temp;
	int ch;
	while((ch = file.get()) != 'e')
	{
		temp += ch;
	}
	int result = atoi(temp.c_str());
	pInt->val = result;
}
void praseString(std::ifstream &file, SLString *pString, int num)
{
	std::string temp;
	temp += num;
	int ch;
	while((ch = file.get()) != ':')
	{
		temp += ch;
	}
	int len = atoi(temp.c_str());
	pString->len = len;
	temp = "";
	for(int i = 0; i < len; ++i)
	{
		temp += file.get();
	}
	pString->val = temp;
}

void praseList(std::ifstream &file, SLList *pList)
{
	pList->content = praseBencoding(file);
}

void praseDictionary(std::ifstream &file, SLDictionary *pD)
{
	int ch = file.get();
	SLString *pString = new SLString;
	praseString(file, pString, ch);
	pD->s = *pString;
	pD->content = praseBencoding(file);
}

std::vector<SLItem> praseBencoding(std::ifstream &file)
{
	int ch;
	SLItem item;
	std::vector<SLItem> result;
	while((ch = file.get()) != 'e')
	{
		if('i' == ch)
		{
			SLInterger *pInt = new SLInterger;
			praseInterger(file, pInt);
			item.type = INTERGER;
			item.ptr = pInt;
		}
		else if('l' == ch)
		{
			SLList *pMyList = new SLList;
			praseList(file, pMyList);
			SLItem *pItem = new SLItem;
			item.type = LIST;
			item.ptr = pMyList;
		}
		else if('d' == ch)
		{
			SLDictionary *pDictionary = new SLDictionary;
			praseDictionary(file, pDictionary);
			item.type = DICTIONARY;
			item.ptr = pDictionary;
		}
		else
		{
			SLString *pString = new SLString;
			praseString(file, pString, ch);
			item.type = STRING;
			item.ptr = pString;
		}
		result.push_back(item);
	}

	return result;
}