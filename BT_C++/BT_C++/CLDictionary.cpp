#include "CLDictionary.h"

CLDictionary::CLDictionary()
{}

CLDictionary::~CLDictionary()
{}

void CLDictionary::praseItem(std::ifstream &file)
{
	file.get();
	m_stringHandle.createItem(STRING);
	m_stringHandle.praseItem(file);
	m_list = praseBencoding(file);
}