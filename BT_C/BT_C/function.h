#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <fstream>
#include "Item.h"

void process(std::string filename);
void praseInterger(std::ifstream &file, SLInterger *pInt);
void praseString(std::ifstream &file, SLString *pString, int num);
void praseList(std::ifstream &file, SLList *pList);
void praseDictionary(std::ifstream &file, SLDictionary *pD);
std::vector<SLItem> praseBencoding(std::ifstream &file);

#endif