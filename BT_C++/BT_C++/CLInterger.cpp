#include "CLInterger.h"
#include <string>

CLInterger::CLInterger() : m_vaule(0)
{}

CLInterger::~CLInterger()
{}

void CLInterger::praseItem(std::ifstream &file)
{
	std::string temp;
	int ch;
	while((ch = file.get()) != 'e')
	{
		temp += ch;
	}
	m_vaule = atoi(temp.c_str());
}