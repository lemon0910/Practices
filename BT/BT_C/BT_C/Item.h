#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

#define INTERGER 0
#define STRING 1
#define LIST 2
#define DICTIONARY 3
struct SLItem
{
	int type;
	void *ptr;
};

struct SLInterger
{
	int val;
};

struct SLString
{
	int len;
	std::string val;
};

struct SLList
{
	std::vector<SLItem> content;
};

struct SLDictionary
{
	SLString s;
	std::vector<SLItem> content;
};

#endif