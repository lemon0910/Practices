#include "CLList.h"

CLList::CLList()
{}

CLList::~CLList()
{}

void CLList::praseItem(std::ifstream &file)
{
	m_list = praseBencoding(file);
}
