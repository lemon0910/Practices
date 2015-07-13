#ifndef CLDICTIONARY_H
#define CLDICTIONARY_H

#include "CLItem.h"

class CLDictionary : public CLItem
{
public:
	explicit CLDictionary();
	~CLDictionary();
	void praseItem(std::ifstream &file);

private:
	CLHandle m_stringHandle;
	std::vector<CLHandle> m_list;
};

#endif