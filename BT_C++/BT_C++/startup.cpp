#include <fstream>
#include <iostream>
#include <string>
#include "CLHandle.h"

void process(std::string filename)
{
	if("" == filename)
	{
		std::cout << "filename is null" << std::endl;
		exit(0);
	}
	std::ifstream file(filename.c_str());
	CLHandle dHandle;
	dHandle.createItem(DICTIONARY);
	dHandle.praseItem(file);
}

int main()
{
	process("1.txt");
	return 0;
}