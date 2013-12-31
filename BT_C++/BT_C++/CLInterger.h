#ifndef CLINTERGER_H
#define CLINTERGER_H

#include "CLItem.h"

class CLInterger : public CLItem
{
public:
	explicit CLInterger();
	~CLInterger();
	void praseItem(std::ifstream &file);
private:
	int m_vaule;
};
#endif