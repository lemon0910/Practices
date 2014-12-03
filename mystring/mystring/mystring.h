#ifndef MYSTRING_H
#define MYSTRING_H

class mystring
{
public:
	mystring();
	mystring(const char *str);
	mystring(const mystring &str);
	~mystring();
	mystring& operator=(const mystring &str);
	int size();
	bool operator==(const mystring &str);
	bool operator<(const mystring &str);
	char operator[](int index);

private:
	char *m_data;
	int m_len;
};

#endif