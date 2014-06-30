#ifndef CLHANDLE_H
#define CLHANDLE_H

#define INTERGER 0
#define STRING 1
#define LIST 2
#define DICTIONARY 3

#include <boost/shared_ptr.hpp>
#include "CLItem.h"

class CLItem;
class CLHandle
{
public:
	explicit CLHandle();
	~CLHandle();
	void createItem(int type);
	void praseItem(std::ifstream &file);
private:
	boost::shared_ptr<CLItem> m_pItem;
	int m_type;
};
#endif