#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mystring.h"
using namespace std;

mystring::mystring() : m_data(nullptr), m_len(0)
{}

mystring::mystring(const char *str)
{
	int len = 0;
	char *temp = const_cast<char*>(str);
	while (*temp != '\0')
	{
		len++;
		temp++;
	}

	m_data = new char[len + 1];
	memcpy(m_data, str, len);
	m_data[len] = '\0';
	m_len = len;
}

mystring::mystring(const mystring& str)
{
	m_len = str.m_len;
	if (0 == m_len)
	{
		m_data = nullptr;
		return;
	}
	m_data = new char[m_len + 1];
	memcpy(m_data, str.m_data, m_len + 1);
}

mystring::~mystring()
{
	if (nullptr != m_data)
		delete[] m_data;
	m_len = 0;
}

mystring& mystring::operator=(const mystring &str)
{
	if (nullptr != m_data)
		delete[] m_data;
	m_len = str.m_len;
	m_data = new char[m_len + 1];
	memcpy(m_data, str.m_data, m_len + 1);

	return *this;
}

int mystring::size()
{
	return m_len;
}

bool mystring::operator==(const mystring &str)
{
	if (m_len == 0 && str.m_len == 0)
		return true;
	if (m_len == 0 || str.m_len == 0)
		return false;
	return strcmp(m_data, str.m_data);
}

bool mystring::operator < (const mystring &str)
{
	if (m_len == 0 && str.m_len == 0)
		return false;
	if (m_len == 0)
		return true;
	if (str.m_len == 0)
		return false;
	return strcmp(m_data, str.m_data) < 0;
}

char mystring::operator[](int index)
{
	return *(m_data + index);
}