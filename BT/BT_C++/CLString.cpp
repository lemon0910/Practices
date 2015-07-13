#include "CLString.h"

CLString::CLString() : m_str(""), m_len(0)
{}

CLString::~CLString()
{}

void CLString::praseItem(std::ifstream &file)
{
	std::string temp;
	int ch;
	while((ch = file.get()) != ':')
	{
		temp += ch;
	}
	m_len = atoi(temp.c_str());
	temp = "";
	for(int i = 0; i < m_len; ++i)
	{
		temp += file.get();
	}
	m_str = temp;
}