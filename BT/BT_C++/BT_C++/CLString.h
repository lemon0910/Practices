#ifndef CLSTRING_H
#define CLSTRING_H

#include "CLItem.h"
#include <string>

class CLString : public CLItem
{
public:
	explicit CLString();
	~CLString();
	void praseItem(std::ifstream &file);
private:
	std::string m_str;
	int m_len;
};
#endif