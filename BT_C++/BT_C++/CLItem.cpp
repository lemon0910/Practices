#include "CLItem.h"
#include <ios>

std::vector<CLHandle> CLItem::praseBencoding(std::ifstream &file)
{
	int ch;
	CLHandle myhandle;
	std::vector<CLHandle> result;
	while((ch = file.get()) != 'e')
	{
		if('i' == ch)
		{
			myhandle.createItem(INTERGER);
		}
		else if('l' == ch)
		{
			myhandle.createItem(LIST);
		}
		else if('d' == ch)
		{
			myhandle.createItem(DICTIONARY);
		}
		else
		{
			file.seekg(-1, std::ios_base::cur);
			myhandle.createItem(STRING);
		}
		myhandle.praseItem(file);
		result.push_back(myhandle);
	}

	return result;
}