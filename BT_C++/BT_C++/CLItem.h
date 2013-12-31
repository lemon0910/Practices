#ifndef CLITEM_H
#define CLITEM_H

#include <fstream>
#include <vector>
#include "CLHandle.h"

class CLHandle;

class CLItem
{
public:
	virtual void praseItem(std::ifstream &file) = 0;
protected:
	std::vector<CLHandle> praseBencoding(std::ifstream &file);
};

#endif