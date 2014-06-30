#include <iostream>
#include "CLHandle.h"
#include "CLInterger.h"
#include "CLString.h"
#include "CLList.h"
#include "CLDictionary.h"

CLHandle::CLHandle()
{}

CLHandle::~CLHandle()
{}

void CLHandle::createItem(int type)
{
	m_type = type;
	switch(m_type)
	{
	case INTERGER:
		m_pItem.reset(new CLInterger);
		break;
	case STRING:
		m_pItem.reset(new CLString);
		break;
	case LIST:
		m_pItem.reset(new CLList);
		break;
	case DICTIONARY:
		m_pItem.reset(new CLDictionary);
		break;
	default:
		std::cout << "type is wrong" << std::endl;
		break;
	}
}

void CLHandle::praseItem(std::ifstream &file)
{
	m_pItem->praseItem(file);
}