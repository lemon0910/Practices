#ifndef CLLIST_H
#define CLLIST_H

#include "CLItem.h"

class CLList : public CLItem
{
public:
	explicit CLList();
	~CLList();
	void praseItem(std::ifstream &file);
private:
	std::vector<CLHandle> m_list;
};
#endif