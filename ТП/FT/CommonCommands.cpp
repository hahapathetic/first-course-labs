#include "CommonCommands.h"
#include <fstream>
#include <algorithm>
#include "IOfmtGuard.h"

void getInvalidMessage(std::wistream& in, std::wostream& out)
{
  iofmtguard guard(out);
  char c = in.get();
  in.putback(c);
  if (c == ' ')
  {
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  out << L"<INVALID COMMAND>" << L'\n';
}

void readFile(const std::wstring& filename, Dictionary& dict)
{
  if ((filename.length() <= 4) || (filename.substr(filename.size() - 4) != L".txt"))
  {
    throw std::invalid_argument("Invalid input file extension. Expected \".txt\".");
  }
  std::wifstream inputFile(filename);

  if (!inputFile)
  {
    throw std::invalid_argument("File not found!\n");
  }

  std::wstring line;
  std::wstring word;
  std::wstring translation;

  while (std::getline(inputFile, line))
  {
    size_t pos = line.find('-');
    if (pos == std::string::npos)
    {
      continue;
    }
    word = line.substr(0, pos - 1);
    if (!isWord(word))
    {
      continue;
    }
    line = line.substr(pos + 2);
    while (!line.empty())
    {
      pos = line.find(',');
      if (pos == std::string::npos)
      {
        translation = line;
        line.clear();
      }
      else
      {
        translation = line.substr(0, pos);
        line = line.substr(pos + 1);
      }
      dict.addWord(word, translation);
    }
  }
}

bool isWord(std::wstring& str)
{
  std::transform(str.begin(), str.end(), str.begin(), std::tolower);
  for (char const& c : str)
  {
    if (std::isalpha(c) == 0 && c != '-')
      return false;
  }
  return true;
}

bool isSentence(std::wstring& str)
{
  const int EXTENDED_ASCII_LOWER_BOUND = 191;
  const int EXTENDED_ASCII_UPPER_BOUND = 256;
  const int YO_CODE = 184;
  std::transform(str.begin(), str.end(), str.begin(), std::tolower);
  for (unsigned char const& c : str)
  {
    if (c != ' ' && std::ispunct(c) == 0 && !((c > EXTENDED_ASCII_LOWER_BOUND) && (c < EXTENDED_ASCII_UPPER_BOUND) || (c == YO_CODE)))
      return false;
  }
  return true;
}
