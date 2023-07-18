#ifndef COMMONCOMMANDS_H
#define COMMONCOMMANDS_H

#include <iostream>
#include "Dictionary.h"

void getInvalidMessage(std::wistream& in, std::wostream& os);
void readFile(const std::wstring& filename, Dictionary& dict);
bool isWord(std::wstring& str);
bool isSentence(std::wstring& str);

#endif
